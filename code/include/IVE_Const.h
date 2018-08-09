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
	NETDATA_TYPE_COMMON,//自描述结构体
	NETDATA_TYPE_IVE_PROTOCOL,//自定协议传输的数据
	NETDATA_TYPE_MAX
}__NetDataType;

typedef enum tagIVEConnType
{
	TYPE_CLIENT,
	TYPE_SERVER,
}__ConnType;

typedef struct tagIVEConnHndl
{
	int number;	//-1是无效的值
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

/*用于网络消息反馈的回调函数*/
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
/*日志级别*/
typedef enum tagIVELogLevel
{
	LOGLEVEL_DEBUG=0,//不存储+不发网络
	LOGLEVEL_INFO,//存磁盘
	LOGLEVEL_WARNING,//存磁盘
	LOGLEVEL_ERROR,//存磁盘+发网络
	LOGLEVEL_FATAL,//致命错误--存磁盘+发网络
}__LogLevel;

typedef enum tagIVEAlarmLevel
{
	ALARMLEVEL_NORMAL=0, //普通警告
	ALARMLEVEL_MIDDLE, //中等
	ALARMLEVEL_SERIOUS, //高级
}__AlarmLevel;

typedef enum tagIVE_Config_Event
{
	IVE_CONFIG_GETSTREAM = 0,
	IVE_CONFIG_SETSTREAM
}IVE_Config_Event;

typedef enum tagIVELogType
{
	LOGTYPE_LOCAL,
	//将来扩展使用
}__LogType;
/*******************************************************************************************/

/*******************************************Status*******************************************/
/***状态发送注册回调--作为服务端***/
typedef int (SC_CDECL *ScStatusSendCallBack)(const char *szWndName, const char *szKey, void* uiUserData, __ConnHndl hConn);
/***状态接收注册回调--作为客户端***/
typedef ScErr (SC_CDECL *ScStatusRecvCallBack)(__ConnHndl hConn, const char *szWndName, const char *szKey, const char *szValue, void* uiUserData);

/*******************************Logger************************************************************/
typedef ScErr (SC_CDECL *ScLoggerCallBack)(__ConnHndl hConn, __LogLevel emlevel, const char* szFileName, const char* szSection, const char *strLogContent, void* uiUserData);
/**************************************Config********************************************/
typedef ScErr (SC_CDECL *ScConfigEventCallBack)(__ConnHndl hConn, IVE_Config_Event eventConfig, void* uiUserData);
/*******************************************************************************************/

/////////////////上传下载相关/////////////////////////////////////////////////////////
typedef enum _tagIVE_NETTOOL_AskModeEvent{
	IVE_NETTOOL_AskModeEvent_SUCCESS=0,
	IVE_NETTOOL_AskModeEvent_TIMEOUT,
	IVE_NETTOOL_AskModeEvent_FAILED,
	IVE_NETTOOL_AskModeEvent_NOTICE, // 通知
	IVE_NETTOOL_AskModeEvent_GOING // 进行中
}IVE_NETTOOL_AskModeEvent;
// 问询目录回调函数 返回SC_ErrYes/SC_ErrNo
typedef ScErr (CALLBACK* FuncIVE_AskModeSetPathCB)(unsigned int nUpLoadID, char szDestPath[256], void* pRegister);
// 上传事件通知函数
typedef ScErr (CALLBACK* FuncIVE_AskModeEventCB)(IVE_NETTOOL_AskModeEvent eventUpLoad, unsigned int nProgress, void* pRegister, unsigned int nUpLoadID, const char* szSavePath);
//////////////////////////////////////////////////////////////////////////


typedef long MsgCategoray;
#define MsgCatUnknown				-1
#define MsgCatRequest				0	//上报, 需要反馈
#define MsgNotice					1	//上报，不需要反馈
#define MsgStatusFeedback			2	//操作状态反馈消息
#define MsgDataFeedback				3	//数据反馈消息
#define IsMsgFeedBack(cat) (((cat) == MsgStatusFeedback) || ((cat) == MsgDataFeedback))

/********************注册用COMMAND***********************************************************************/
/***IVE_LOGGER使用***/
#define COMMOND_IVE_LOGGER_ADDLOG "IVE_LOGGER_COMMAND_ADDLOG"
/***IVE_Alarm***/
#define COMMOND_IVE_LOGGER_ADDALARM		"IVE_LOGGER_COMMAND_ADDALARM"
#define COMMOND_IVE_LOGGER_RISEALARM			"IVE_LOGGER_COMMAND_RISEALARM"
#define COMMOND_IVE_LOGGER_CANCELALARM		"IVE_LOGGER_COMMAND_CANCELALARM"

/***IVE_STATUS使用***/
#define COMMOND_IVE_STATUS_SETVALUE "IVE_STATUS_COMMOND_SETVALUE"
#define COMMOND_IVE_STATUS_GETVALUE "IVE_STATUS_COMMOND_GETVALUE"

/***IVE_CONFIG使用***/
#define COMMOND_IVE_CONFIG_GETSTREAM	"IVE_CONFIG_COMMOND_GETSTREAM"
#define COMMOND_IVE_CONFIG_SETSTREAM	"IVE_CONFIG_COMMOND_SETSTREAM"
#define COMMOND_IVE_CONFIG_SETITEM			"IVE_CONFIG_COMMOND_SETITEM"

/***IVE 网络连接改变 事件回调***/
#define COMMOND_IVE_EVENT_CONN_ADD "IVE_EVENT_COMMAND_ADDCONN"
#define COMMOND_IVE_EVENT_CONN_DEL "IVE_EVENT_COMMAND_DELCONN"
/*******************************************************************************************/

typedef ScErr (SC_STDCALL *CommandForwardCB)(const char* sCommand, void *pRecvData, __NetDataType enRecvType, NetTransferData stNetTransferData, __ConnHndl hConn, void* uiUserData, MsgCategoray cat);
#endif
