#include "IVECommunication.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sys/timeb.h>
#include <sys/types.h>
#include "commonMethod.h"
#ifndef WIN32
#include <pthread.h>
#include <unistd.h>
#endif

using namespace std;

CIVECommunication::CIVECommunication()
{
	m_msgList = NULL;
	m_msgListMutex = NULL;
	m_serverIp = "127.0.0.1";
	m_serverPort = 9999;
	m_IVEReceiveNum = 0;
}

CIVECommunication::~CIVECommunication()
{
	for(int index = 0; index<m_pidList.size(); index++)
	{
		pthread_join(m_pidList[index],NULL);
	}
	DestroyClient();
}

ScErr SC_STDCALL MyIVECommandCB(const char* sCommand, void *pRecvData, __NetDataType enRecvType, NetTransferData stNetTransferData, __ConnHndl hConn, void* uiUserData)
{
	
	long long begin = getSystemTime();
	ScErr errRet = SC_ErrSuccess;
	
	CIVECommunication* pHand = (CIVECommunication*)uiUserData;

	if (strcmp(sCommand, COMMOND_IVE_RES_RESULT) == 0)//客户端向服务器发送结果数据
	{
		int ret = 0;
		HCommonObj hCom = (HCommonObj*)pRecvData;
		if((GetValueTypeByKey(hCom, "data") != DC_CHARARR))
			errRet = SC_ErrReceiveDataErr;
		unsigned int nType = 0;
		char *pJsonRES = NULL;
		unsigned int nStrlen = 0;
		if(GetValueByKey(hCom, "data", &nType, &pJsonRES, &nStrlen) != SC_ErrSuccess)
			errRet = SC_ErrDataTransErr;
		//string strJson = pJsonRES
		
		//创建反馈信息，通知客户端数据接收成功
		HCommonObj hFeedBackObj = NULL;
		ScErr errRet = CreateCommonObj(&hFeedBackObj);
		if(errRet != SC_ErrSuccess)
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "IVEServer.log", __FUNCTION__, "创建应答句柄失败 err = %d",errRet);
		}
		
		AddKeyValue(hFeedBackObj, "result", DC_INT, &ret, sizeof(ret));
		const char *Retbuf = "OK";
		AddKeyValue(hFeedBackObj, "result_desc", DC_CHARARR, &Retbuf, strlen(Retbuf)+1);
		//IVE_Logger_AddLog(LOGLEVEL_WARNING, "IVEServer.log", __FUNCTION__, "ret = %d",ret);
		errRet = IVE_NET_SendMsgFeedBack(hConn, sCommand, stNetTransferData, enRecvType, hFeedBackObj, MsgDataFeedback);
		if(errRet != SC_ErrSuccess)
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "IVEServer.log", __FUNCTION__, "发送应答消息失败 err = %d",errRet);
		}
		DestroyCommonObj(hFeedBackObj);
	
		//IVE_Logger_AddLog(LOGLEVEL_WARNING, "IVEServer.log", __FUNCTION__, "数据准备放入队列");
		pthread_mutex_lock(pHand->m_msgListMutex);
		if(pHand->m_msgList->size()<500)
		{
			msgInfo ansstr;
			time(&ansstr.msgStart);
			ansstr.strMsg = pJsonRES;
			pHand->m_IVEReceiveNum++;
			pHand->m_msgList->push_back(ansstr); //放入队列中，由sesson线程进行处理
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "IVEServer.log", __FUNCTION__, "接收分析数据条数 = %d",pHand->m_IVEReceiveNum);
		}
        pthread_mutex_unlock(pHand->m_msgListMutex);
		long long end = getSystemTime();
	}
	else if(strcmp(COMMOND_IVE_GET_DEVICEID, sCommand) == 0)//客户端向服务器获取设备ID的信息
	{
		HCommonObj hFeedBackObj = NULL;
		ScErr errRet = CreateCommonObj(&hFeedBackObj);
		const char* szDeviceID = pHand->m_deviceID.c_str();;//设备ID信息
		AddKeyValue(hFeedBackObj, "result", DC_CHARARR, &szDeviceID, strlen(szDeviceID)+1);
		//AddKeyValue(hFeedBackObj, "result_desc", DC_CHARARR, &, );
		IVE_NET_SendMsgFeedBack(hConn, sCommand, stNetTransferData, enRecvType, hFeedBackObj, MsgDataFeedback);
		DestroyCommonObj(hFeedBackObj);
	}
	else if(strcmp(COMMOND_IVE_EVENT_CONN_DEL, sCommand) == 0)
	{
		//客户端断开连接
	}
	else if(strcmp(COMMOND_IVE_EVENT_CONN_ADD, sCommand) == 0)
	{
		//客户端成功连接到服务器 
	}
	return errRet;
}

ScErr CIVECommunication::CreateIVEServer()
{
	int nPort = m_serverPort;
	//IVE_SDK_Init(5, 1024, "IVEServer.txt");
	//IVE_SDK_Start();
	ScErr errRet = IVE_SDK_StartNetWork(m_serverIp.c_str(), m_serverPort, TYPE_SERVER);
	if(SC_ErrSuccess != errRet)
	{
		printf("IVE_SDK_StartNetWork Failed-%d", errRet);
	}

	IVE_NET_RegisterCommandCB(COMMOND_IVE_EVENT_CONN_ADD, MyIVECommandCB, (void*)NULL);
	IVE_NET_RegisterCommandCB(COMMOND_IVE_EVENT_CONN_DEL, MyIVECommandCB, (void*)NULL);
	IVE_NET_RegisterCommandCB(COMMOND_IVE_RES_RESULT,MyIVECommandCB,(void*)this);
	IVE_NET_RegisterCommandCB(COMMOND_IVE_GET_DEVICEID,MyIVECommandCB,(void*)this);

	return SC_ErrSuccess;
}

ScErr CIVECommunication::CreateIVEClient()
{
	ScErr errRet = SC_ErrSuccess;
	vector<dataImportInfo>::iterator it= m_dataImportServList.begin();
	for (it;it!=m_dataImportServList.end();it++)
	{
		ScErr errRet = IVE_SDK_StartNetWork(it->strIp.c_str(), it->nPort, TYPE_CLIENT);
		if(SC_ErrSuccess != errRet)
		{
			return errRet;
		}
	}
	return errRet;
} 

ScErr CIVECommunication::GetIVEClientHandle(dataImportInfo& dataImport)
{
	ScErr errRet = SC_ErrSuccess;
	int nHandleCnt = 0;

	dataImport.hObj = NULL;
	while (1)
	{
		errRet = IVE_NET_GetConnHndlsByAddr(dataImport.strIp.c_str(), dataImport.nPort, TYPE_CLIENT, &dataImport.pHandle, &nHandleCnt);
		if(SC_ErrSuccess!=errRet)
		{	
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "获取和 data_import 连接句柄失败");
			sleep(1);
			continue;
		}
		if (!dataImport.pHandle)
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "获取和 data_import 连接句柄失败");
			sleep(1);
			continue;
		}
		errRet = CreateCommonObj(&dataImport.hObj);
		if(errRet != SC_ErrSuccess)
		{
			if (dataImport.pHandle)
			{
				IVE_NET_PutConnHndls(dataImport.pHandle);
				dataImport.pHandle = NULL;
			}
		}
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "获取和 data_import 连接句柄成功");
		break;
		sleep(1);
		continue;
	}

	return errRet;
}

ScErr	CIVECommunication::DestroyClient()
{
	vector<dataImportInfo>::iterator it= m_dataImportServList.begin();
	for (it;it!=m_dataImportServList.end();it++)
	{
		if (it->hObj)
		{
			DestroyCommonObj(it->hObj);
		}
		if (it->pHandle)
		{
			IVE_NET_PutConnHndls(it->pHandle);
			it->pHandle = NULL;
		}
	}
}

void* SendSuccessToDataImport(void* args)
{
	ScErr errRet = SC_ErrSuccess;
	//int number = int(args);
	//CIVECommunication* pHand = (CIVECommunication*)args;

	dataImportInfo* pHand = (dataImportInfo*)args;

	pHand->mFunc(*pHand);

	while(1)
	{
		if (pHand->msgIdlist.size()==0)
		{
			usleep(100);
			continue;
		}
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "feedback.log", __FUNCTION__, "ip = %s | msgIdlist size = %d",pHand->strIp.c_str(),pHand->msgIdlist.size());
		string strID =pHand->msgIdlist.front();
		pHand->msgIdlist.pop_front();
		const char* szID = strID.c_str();

		AddKeyValue(pHand->hObj, "pic_id", DC_CHARARR, &szID, strID.length()+1);
		char tmpBuf[255] = {0};
		strncpy(tmpBuf, szID, 50);

		void *pFeedBack =NULL;
		__NetDataType nType = NETDATA_TYPE_COMMON;
		long long start=getSystemTime();
		//IVE_Logger_AddLog(LOGLEVEL_WARNING, "IVEServer.log", __FUNCTION__, "ip = %s port = %d",it->strIp.c_str(),it->nPort);
		errRet = IVE_NET_SendSyncMsgEx(pHand->pHandle[0], COMMOND_IVE_SEND_RESULT, NETDATA_TYPE_IVE_PROTOCOL, pHand->hObj, MsgCatRequest, NULL, &pFeedBack, &nType, 5);
		long long end=getSystemTime();
		if(errRet != SC_ErrSuccess) //反馈
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "feedback.log", __FUNCTION__, "data_import 接收反馈失败 err = %d|ip = %s|port = %d",errRet,pHand->strIp.c_str(),pHand->nPort);
			pHand->msgIdlist.push_back(strID);
			while (pHand->mFunc(*pHand) != SC_ErrSuccess)
			{
				sleep(1);
			}
		}
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "feedback.log", __FUNCTION__, "data_import 接收反馈成功 耗时 = %d|ip = %s|port = %d",end-start,pHand->strIp.c_str(),pHand->nPort);
	}
	return NULL;
} 

void CIVECommunication::DestroyServer()
{
	IVE_SDK_EndNetWork(m_serverIp.c_str(), m_serverPort, TYPE_SERVER);
}

//////////////////////////////////////////////////////////////////////////
void   CIVECommunication::SetIVEServer(string strIp,int nPort)
{
	m_serverIp = strIp;
	m_serverPort = nPort;
}

void  CIVECommunication::SetMsgList(list<msgInfo>* msgList)
{
	m_msgList = msgList;
}

//list<string>&  CIVECommunication::GetMsgIdList()
//{
//	return ;
//}

void  CIVECommunication::SetMsgListMutex(pthread_mutex_t* lock)
{
	if (lock)
	{
		m_msgListMutex = lock;
	}
}

void  CIVECommunication::SetDeviceID(string deviceID)
{
	m_deviceID = deviceID;
}

ScErr CIVECommunication::CreateClientThread()
{
	for(int index=0; index<m_dataImportServList.size(); index++)
	{
		pthread_t ptid;
		if(0 != pthread_create(&ptid, NULL,SendSuccessToDataImport,(void*)&m_dataImportServList[index]))
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建第 %d 个反馈线程失败...",index);
		}
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建第 %d 个反馈线程成功...",index);
		m_pidList.push_back(ptid);
	}
}