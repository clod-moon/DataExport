#ifndef IVE_CONST_H_
#define IVE_CONST_H_

#include "ScType.h"
#ifdef WIN32
#include <WinSock2.h>
#endif

#ifdef WIN32
	#include <windef.h>
#else
	#include <limits.h>

	#ifndef MAX_PATH
	#define MAX_PATH PATH_MAX
	#endif
#endif

#include <limits.h>

typedef enum tagNetDataType
{
	NETDATA_TYPE_CONFIG,   //HSCConfig
	NETDATA_TYPE_COMMON,//�������ṹ��
	NETDATA_TYPE_IVE_PROTOCOL,//�Զ�Э�鴫�������
	NETDATA_TYPE_MAX
}__NetDataType;

typedef enum tagIVEConnType
{
	TYPE_CLIENT,
	TYPE_SERVER,
}__ConnType;

typedef struct tagIVEConnHndl
{
	int number;	//-1����Ч��ֵ
}__ConnHndl;
typedef struct tagNetTransferData
{
	const char* szMsgID;
}NetTransferData;

#ifndef DEF_IVE_NetWorkAddr
#define DEF_IVE_NetWorkAddr
typedef struct _tagIVE_NetWorkAddr
{
	__ConnType enType;
	int port;
	char szIP[16];
	char szServiceType[40];
}IVE_NetWorkAddr;
#endif

/*����������Ϣ�����Ļص�����*/
typedef ScErr (SC_STDCALL *CommandCB)(const char* sCommand, void *pRecvData, __NetDataType enRecvType, NetTransferData stNetTransferData, __ConnHndl hConn, void* uiUserData);



typedef struct tagIVEConnInfo
{
	__ConnType emType;
	int		   nPort;
	char 	   szSrcIp[20];
	char 	   szDstIp[20];
	SOCKET	   sockConn;
}__ConnInfo;

/***********************************************Logger**********************************/
/*��־����*/
typedef enum tagIVELogLevel
{
	LOGLEVEL_DEBUG=0,//���洢+��������
	LOGLEVEL_INFO,//�����
	LOGLEVEL_WARNING,//�����
	LOGLEVEL_ERROR,//�����+������
	LOGLEVEL_FATAL,//��������--�����+������
}__LogLevel;

typedef enum tagIVEAlarmLevel
{
	ALARMLEVEL_NORMAL=0, //��ͨ����
	ALARMLEVEL_MIDDLE, //�е�
	ALARMLEVEL_SERIOUS, //�߼�
}__AlarmLevel;

typedef enum tagIVE_Config_Event
{
	IVE_CONFIG_GETSTREAM = 0,
	IVE_CONFIG_SETSTREAM
}IVE_Config_Event;

typedef enum tagIVELogType
{
	LOGTYPE_LOCAL,
	//������չʹ��
}__LogType;
/*******************************************************************************************/

/*******************************************Status*******************************************/
/***״̬����ע��ص�--��Ϊ�����***/
typedef int (SC_CDECL *ScStatusSendCallBack)(const char *szWndName, const char *szKey, void* uiUserData, __ConnHndl hConn);
/***״̬����ע��ص�--��Ϊ�ͻ���***/
typedef ScErr (SC_CDECL *ScStatusRecvCallBack)(__ConnHndl hConn, const char *szWndName, const char *szKey, const char *szValue, void* uiUserData);

/*******************************Logger************************************************************/
typedef ScErr (SC_CDECL *ScLoggerCallBack)(__ConnHndl hConn, __LogLevel emlevel, const char* szFileName, const char* szSection, const char *strLogContent, void* uiUserData);
/**************************************Config********************************************/
typedef ScErr (SC_CDECL *ScConfigEventCallBack)(__ConnHndl hConn, IVE_Config_Event eventConfig, void* uiUserData);
/*******************************************************************************************/

/////////////////�ϴ��������/////////////////////////////////////////////////////////
typedef enum _tagIVE_NETTOOL_AskModeEvent{
	IVE_NETTOOL_AskModeEvent_SUCCESS=0,
	IVE_NETTOOL_AskModeEvent_TIMEOUT,
	IVE_NETTOOL_AskModeEvent_FAILED,
	IVE_NETTOOL_AskModeEvent_NOTICE, // ֪ͨ
	IVE_NETTOOL_AskModeEvent_GOING // ������
}IVE_NETTOOL_AskModeEvent;
// ��ѯĿ¼�ص����� ����SC_ErrYes/SC_ErrNo
typedef ScErr (CALLBACK* FuncIVE_AskModeSetPathCB)(unsigned int nUpLoadID, char szDestPath[256], void* pRegister);
// �ϴ��¼�֪ͨ����
typedef ScErr (CALLBACK* FuncIVE_AskModeEventCB)(IVE_NETTOOL_AskModeEvent eventUpLoad, unsigned int nProgress, void* pRegister, unsigned int nUpLoadID, const char* szSavePath);
//////////////////////////////////////////////////////////////////////////


typedef long MsgCategoray;
#define MsgCatUnknown				-1
#define MsgCatRequest				0	//�ϱ�, ��Ҫ����
#define MsgNotice					1	//�ϱ�������Ҫ����
#define MsgStatusFeedback			2	//����״̬������Ϣ
#define MsgDataFeedback				3	//���ݷ�����Ϣ
#define IsMsgFeedBack(cat) (((cat) == MsgStatusFeedback) || ((cat) == MsgDataFeedback))

/********************ע����COMMAND***********************************************************************/
/***IVE_LOGGERʹ��***/
#define COMMOND_IVE_LOGGER_ADDLOG "IVE_LOGGER_COMMAND_ADDLOG"
/***IVE_Alarm***/
#define COMMOND_IVE_LOGGER_ADDALARM		"IVE_LOGGER_COMMAND_ADDALARM"
#define COMMOND_IVE_LOGGER_RISEALARM			"IVE_LOGGER_COMMAND_RISEALARM"
#define COMMOND_IVE_LOGGER_CANCELALARM		"IVE_LOGGER_COMMAND_CANCELALARM"

/***IVE_STATUSʹ��***/
#define COMMOND_IVE_STATUS_SETVALUE "IVE_STATUS_COMMOND_SETVALUE"
#define COMMOND_IVE_STATUS_GETVALUE "IVE_STATUS_COMMOND_GETVALUE"

/***IVE_CONFIGʹ��***/
#define COMMOND_IVE_CONFIG_GETSTREAM	"IVE_CONFIG_COMMOND_GETSTREAM"
#define COMMOND_IVE_CONFIG_SETSTREAM	"IVE_CONFIG_COMMOND_SETSTREAM"
#define COMMOND_IVE_CONFIG_SETITEM			"IVE_CONFIG_COMMOND_SETITEM"

/***IVE �������Ӹı� �¼��ص�***/
#define COMMOND_IVE_EVENT_CONN_ADD "IVE_EVENT_COMMAND_ADDCONN"
#define COMMOND_IVE_EVENT_CONN_DEL "IVE_EVENT_COMMAND_DELCONN"
/*******************************************************************************************/

typedef ScErr (SC_STDCALL *CommandForwardCB)(const char* sCommand, void *pRecvData, __NetDataType enRecvType, NetTransferData stNetTransferData, __ConnHndl hConn, void* uiUserData, MsgCategoray cat);
#endif
