#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <unistd.h>
#include <signal.h> 
#include <sys/param.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "GetConfig.h"
#include "osa_syslog.h"
#include "json/json.h"
#include "DevInitMethod.h"
#include "httpClient.h"
#include <sys/timeb.h>
#include "IVE_SDK_Export.h"
#include "CommonObjExport.h"
#include "commonMethod.h"
#include "IVECommunication.h"
using namespace std;
#define  FILENAME  "config.ini"

pthread_mutex_t request_list_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t feedback_list_lock = PTHREAD_MUTEX_INITIALIZER;

int  number;
static bool isReconneted;

map<string,string> config;
list<msgInfo> ans_list;
int putTimes;
int putNums;

//工作线程，回调函数
void* working(void *arg); 

//计数线程，回调函数
void* scalerNum(void* arg);

//自动重连线程，回调函数
void* autoReconnect(void* args);

//测试线程，回调函数
void* testPthead(void* args);

//重发数据到平台
ScErr resendMsgTOJava(string& strMsg,int num);


int Init(map<string,string>&config,CIVECommunication& iveDataExport)
{
	vector<string> veIpArr;

	int nMaxSaveLogFileDay = atoi(config["MaxSaveLogFileDay"].c_str());

	int nMaxFileSize       = atoi(config["MaxLogFileSize"].c_str());

	string 	szSaveLogPath  = config["SaveLogPath"].c_str();	

	if(!IVE_SDK_Init(nMaxSaveLogFileDay,nMaxFileSize*1024*1024,szSaveLogPath.c_str()))
	{
		return -1;
	}

	if(!IVE_SDK_Start())
	{
		return -1;
	}

	iveDataExport.SetDeviceID(config["user_unid"]);
	iveDataExport.SetIVEServer(config["ip"],atoi(config["port"].c_str()));
	iveDataExport.SetMsgListMutex(&request_list_lock);
	iveDataExport.SetMsgList(&ans_list);
	findRoundName(config,"DataImportIP", veIpArr);
	for(int i =0;i<veIpArr.size();i++)
	{
		dataImportInfo tempInfo;
		tempInfo.strIp = veIpArr[i];
		tempInfo.nPort = atoi(config["DataImportPort"].c_str());
		tempInfo.pHandle = NULL;
		tempInfo.hObj = NULL;
		tempInfo.mFunc = CIVECommunication::GetIVEClientHandle;
		iveDataExport.m_dataImportServList.push_back(tempInfo);
	}

	if(iveDataExport.CreateIVEClient() != SC_ErrSuccess)
	{
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建IVEClient 失败 err = %d...");
		return -1;
	}

	if(iveDataExport.CreateClientThread()!=SC_ErrSuccess)
	{
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建反馈线程失败...");
		return -1;
	}


	return 0;
}

void unInit(vector<pthread_t>& vptid)
{
	for(int index = 0; index<vptid.size(); index++)
	{
		pthread_join(vptid[index],NULL);
	}
	IVE_SDK_End();
	IVE_SDK_UnInit();
}

int CreateFunctionThread(map<string,string>&config,vector<pthread_t>& vptid)
{
	pthread_t reConnecThreadId;
	if(0 != pthread_create(&reConnecThreadId, NULL,autoReconnect, NULL))
	{
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建重连线程失败...");
	}
	vptid.push_back(reConnecThreadId);
	sleep(1);


	pthread_t scalerNumThreadId;
	if(0 != pthread_create(&scalerNumThreadId, NULL,scalerNum, NULL))
	{
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建每分钟统计转发总数线程失败...");
	}
	vptid.push_back(scalerNumThreadId);

	putNums = atoi(config["putNums"].c_str());
	putTimes = atoi(config["putTimes"].c_str());

	//IVE_Logger_AddLog(LOGLEVEL_WARNING, "IVEServer.log", __FUNCTION__, "putNums = %d ,putTimes = %d",putNums,putTimes);
	//{
	//	pthread_t ptidTest;
	//	if(0 != pthread_create(&ptidTest, NULL, testPthead, NULL))
	//	{
	//		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建test线程失败...");
	//	}
	//	vptid.push_back(ptidTest);
	//}


	return 0;
}

int CreateWorkThread(map<string,string>&config,vector<pthread_t>& vptid,CIVECommunication& iveDataExport)
{
	int pthreadNum = atoi(config["pthreadNum"].c_str());
	for(int index=0; index<pthreadNum; index++)
	{
		pthread_t ptid;
		if(0 != pthread_create(&ptid, NULL, working, (void*)&iveDataExport))
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建第 %d 个工作线程失败...",index);
		}
		vptid.push_back(ptid);
	}
	IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建 %d 个线程 ...",pthreadNum);

	return 0;
}

void* working(void *arg)
{
	CIVECommunication* pHand = (CIVECommunication*)arg;
	msgInfo ansstr;
	while(1)
    {
		pthread_mutex_lock(&request_list_lock);
        if(ans_list.empty()||isReconneted == false)
        {
			pthread_mutex_unlock(&request_list_lock);
        	usleep(1000);
        	continue;
        }
        ansstr = ans_list.front();
        ans_list.pop_front(); //从list中取出第一个请求进行处理
        pthread_mutex_unlock(&request_list_lock);
		map<string,string> header;
		//IVE_Logger_AddLog(LOGLEVEL_DEBUG, "main.log", __FUNCTION__, "atoken = %s",config["atoken"].c_str());
		header["authorization"] = config["atoken"];
		
		time_t msgEnd;
		time(&msgEnd);
		if(getDiffTimeSec(msgEnd,ansstr.msgStart)>20)
		{
			continue;
		}

		string strPicID;
		string subId="\"ID\":\""; 
		//int position1,position2;
		//position1=ansstr.strMsg.find(subId)+subId.length();
		//if(position1 < 0 )
		//{
		//	IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "未获取到 ID");
		//}
		//else
		//{
		//	position2=ansstr.strMsg.find("\"",position1);  
		//	int len = position2-position1;
		//	strPicID.assign(ansstr.strMsg,position1,len);
		//} 
		getSubStr(ansstr.strMsg,subId,strPicID);
		string result;
		int timeout = atoi(config["timeout"].c_str());
		long long begin = getSystemTime();
		//IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "向平台 %s 地址发送数据",config["http_url"].c_str());
		int ret = netPost(config["http_url"],ansstr.strMsg,timeout,result,header);
		if (ret!=0)
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "do_session netPost failed");
			isReconneted = false;
			continue;
		}
		long long end = getSystemTime();
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "receve.log", __FUNCTION__, "result = [%s]",result.c_str());
		if(result.empty())
		{
			number++;
			//为空不是图片任务，不需要反馈
			if(!strPicID.empty())
			{
				for(int i =0;i<pHand->m_dataImportServList.size();i++)
				{
					pHand->m_dataImportServList[i].msgIdlist.push_back(strPicID);
				}
			}
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "未发送条数 = %d  |  已发送条数 = %d",ans_list.size(),number);
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "receve.log", __FUNCTION__, "平台接收时间 = %lld",end-begin);
			usleep(1000);
			continue;
		}
		string strSubTaskID;
		subId="\"subtask_id\":\"";
		getSubStr(ansstr.strMsg,subId,strSubTaskID);
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "error.log", __FUNCTION__, "平台接收失败 subTaskID = %s",strSubTaskID.c_str());
		Json::Value root;
		Json::Reader reader;
		if (reader.parse(result,root))
		{
			int ecode = root["ecode"].asInt();
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "ecode = %d",ecode);
			if(ecode==200||ecode==1004010006||ecode==1004010007)
			{
				IVE_Logger_AddLog(LOGLEVEL_WARNING, "error.log", __FUNCTION__, "平台反馈 json 不合法 数据ID = %s",strPicID.c_str());
				continue;
			}
			else
			{
				IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "平台接收失败,重新发送");
				//pthread_mutex_lock(&request_list_lock);
				//ans_list.push_back(ansstr); //放入队列中，由sesson线程进行处理
				if(ecode==1004010001 || ecode==1004010002)
				{
					IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "atoken 过期，重新登录");
					isReconneted = false;
				}

				//inargs->m_isRecive = true;
				//pthread_mutex_unlock(&request_list_lock);
				usleep(1000);
			}
		}
		else
		{
			//pthread_mutex_lock(&request_list_lock);
			//ans_list.push_back(ansstr); 
			//pthread_mutex_unlock(&request_list_lock);
			//IVE_Logger_AddLog(LOGLEVEL_WARNING, "error.log", __FUNCTION__, "平台失效地址是 %s",config["http_url"].c_str());
			usleep(1000);
			isReconneted = false;
		}
	}
    return NULL;
}

void* scalerNum(void* arg)
{
	long long startNum = 0;
	char logDay[64]   ={0};
	struct tm*		  tmTime = NULL;
	size_t			  timeLen = 0;
	time_t			  tTime = 0;	
	tTime =           time(NULL);
	tmTime = localtime(&tTime);
	timeLen = strftime(logDay, 33, "%Y%m%d", tmTime);
	string temLogDay   = logDay;
	while(1)
	{
		sleep(60);
		int counter = number - startNum;
		syslog_info("ervery 1 minute transport = %d ",counter);
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "ervery 1 minute transport = %d ",counter);
		memset(logDay,0x00,sizeof(logDay));
		tTime   = time(NULL);
		tmTime  = localtime(&tTime);
		timeLen = strftime(logDay, 33, "%Y%m%d", tmTime);
		if(temLogDay.compare(logDay) != 0)
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "total.log", __FUNCTION__, "%s 总共转发的数量 = %d ",temLogDay.c_str(),number);
			number = 0;
			startNum = number;
			temLogDay = logDay;
		}
		else
		{
			startNum = number;
		}
	}
}

void* autoReconnect(void* args)
{
	int i =0;
	string errmsg;
	while(1)
	{
		if(isReconneted)
		{
			sleep(1);
			continue;
		}
		if(i >0)
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "平台地址失效，重新登录获取");
		}
		if (DevLogin(config))
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "line=%d, 登录失败",__LINE__);
			sleep(1);
			continue;
		}
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "line=%d, 登录成功",__LINE__);
		syslog_info("DevLogin ok");
		if (DevRegister(config,errmsg))
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "line=%d, 注册失败",__LINE__);
			sleep(1);
			continue;
		}
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "line=%d, 注册成功",__LINE__);
		syslog_info("DevRegister ok");
		if (DevGetDataAccpetUrl(config,errmsg))
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "line=%d, 获取接收地址失败",__LINE__);
			sleep(1);
			continue;
		}
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "line=%d, 获取接收地址成功",__LINE__);
		if(i >0)
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "line=%d, 重新登录，注册，获取接收地址成功",__LINE__);
		}
		isReconneted = true;
		i++;
	}
	return NULL;
}

//void* sendToDataImport(void* args)
//{
//	while( GetIVEClientHandle(dataImportInfoList)!=SC_ErrSuccess)
//	{
//		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "获取和 data_import 连接句柄失败");
//		sleep(1);
//	}
//	ScErr errRet = SendSuccessToDataImport(dataImportInfoList,picIDlist,feedback_list_lock);
//	if (errRet!= SC_ErrSuccess)
//	{
//		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "启动发送反馈模块失败");
//		return NULL;
//	}
//	
//	errRet = DestroyClient(dataImportInfoList);
//	if (errRet!= SC_ErrSuccess)
//	{
//		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "销毁 data_import 连接句柄失败");
//		return NULL;
//	}
//}

ScErr resendMsgTOJava(string& strMsg,int num)
{
	ScErr errRet = SC_ErrNetSendFailed;
	string result;
	map<string,string> header;
	for (int i=0;i<num;i++)
	{
		int ret = netPost(config["http_url"],strMsg,10,result,header);
		if (ret!=0)
		{
			IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "do_session netPost failed");
		}
		else
		{
			return SC_ErrSuccess;
		}
	}
	isReconneted = false;
	return errRet;
}

void* testPthead(void* args)
{
	msgInfo testInfo;
	char* buf = new char[1024*1024*2];
	memset(buf,0x00,1024*1024*2);
	IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "putNums = %d ,putTimes = %d",putNums,putTimes);
	readfile("data.txt",buf);
	time(&testInfo.msgStart);
	testInfo.strMsg = buf;
	for (int i =0;i<putNums;i++)
	{
		pthread_mutex_lock(&request_list_lock);
		for (int j = 0;j<putTimes;j++)
		{
			//IVE_Logger_AddLog(LOGLEVEL_WARNING, "IVEServer.log", __FUNCTION__, "aaaaaaaaaaa ");
			if(ans_list.size()<500)
			{
				//inargs->m_index++;
				ans_list.push_back(testInfo); //放入队列中，由sesson线程进行处理
				IVE_Logger_AddLog(LOGLEVEL_WARNING, "IVEServer.log", __FUNCTION__, "接收分析数据条数");
			}
		}
		pthread_mutex_unlock(&request_list_lock);
		sleep(1);
	}
	delete buf;

	return NULL;
}



int main(int argc,char** args)
{
	number = 0;
	isReconneted = false;
	vector<pthread_t>vptid;

	if (argc<2)
	{
		ReadConfig(FILENAME,config);
	}
	else if(argc == 2)
	{
		string strConfigPath = args[1];
		ReadConfig(strConfigPath,config);
	}

	CIVECommunication iveDataExport;

	if(Init(config,iveDataExport)<0)
	{
		syslog_info("init failed ");
		return -1;
	}

	IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "IVE_Logger_AddLog 调用成功");

	if(CreateFunctionThread(config,vptid)<0)
	{
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建功能线程失败");
		return -1;
	}

	if(CreateWorkThread(config,vptid,iveDataExport)<0)
	{
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "创建工作线程失败");
		return -1;
	}

	iveDataExport.CreateIVEServer();

	while(1)
	{
		//IVE_Logger_AddLog(LOGLEVEL_DEBUG, "main.log", __FUNCTION__, "Waiting for client... ...");
		sleep(1);
	}

	iveDataExport.DestroyServer();

	unInit(vptid);

	return 0;
}