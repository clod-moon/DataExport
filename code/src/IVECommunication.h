#ifndef _IVE_COMMUNICATION_H_
#define _IVE_COMMUNICATION_H_
#include "IVE_SDK_Export.h"
#include "CommonObjExport.h"
#include "commonMethod.h"
#include "ScErr.h"
#include <stdio.h>
#include <string>
#include <list>
#include <map>
#include <stdlib.h>
using namespace std;

#define COMMOND_IVE_RES_RESULT "IVE_EVENT_COMMAND_RES_RESULT" //上传数据结果
#define COMMOND_IVE_GET_DEVICEID "IVE_EVENT_COMMAND_GET_DEVICEID"//获取设备ID
#define COMMOND_IVE_SEND_RESULT  "IVE_EVENT_COMMAND_PIC_FINISHED"


class CIVECommunication
{
public:
		CIVECommunication();
		~CIVECommunication();
public: 
		
		ScErr CreateClientThread();

		void  SetDeviceID(string deviceID);

		void  SetIVEServer(const string strIp,const int nPort);

		void  SetMsgList(list<msgInfo>* msgList);

		void  SetMsgListMutex(pthread_mutex_t* lock);

		list<string>&  GetMsgIdList();

		ScErr CreateIVEClient();

		ScErr CreateIVEServer();

		//void SendSuccessToDataImport(void* args);

		void DestroyServer();

		static ScErr GetIVEClientHandle(dataImportInfo& dataImport);

		ScErr DestroyClient();

		//ScErr SC_STDCALL MyIVECommandCB(const char* sCommand, void *pRecvData, __NetDataType enRecvType, NetTransferData stNetTransferData, __ConnHndl hConn, void* uiUserData);
private:
		
public:
		vector<dataImportInfo>			m_dataImportServList;
		string							m_deviceID;
		pthread_mutex_t*				m_msgListMutex;
		list<msgInfo>*					m_msgList;
		int								m_IVEReceiveNum;
private:
//#ifndef WIN32
		pthread_mutex_t         m_msgIdListMutex;

		vector<pthread_t>		m_pidList;
//#endif
private:
		string					m_serverIp;
		int						m_serverPort;
private:
		
};

#endif //IVE_SERVER_TEST_H
