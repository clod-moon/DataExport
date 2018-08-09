/************************************************************************/
/* 对于连接的操作为使用__ConnHndl句柄
*/
/************************************************************************/
#ifndef IVE_SDK_EXPORT_H
#define IVE_SDK_EXPORT_H
#include "IContainerBase.h"
#include "CommonObjExport.h"
#include "IVE_Const.h"



/******************************************/
/*初始化IVE
	nMaxFolderNum:日志文件夹限定数量
	nMaxFileSize:日志文件最大byte
	szFilePath:日志文件路径
*/
/******************************************/
SCAPI(BOOL) IVE_SDK_Init(int nMaxSaveFileDay, int nMaxFileSize, const char* szFilePath);

/******************************************/
/*反初始化IVE*/
/******************************************/
SCAPI(void) IVE_SDK_UnInit();

SCAPI(BOOL) IVE_SDK_Start();
SCAPI(void) IVE_SDK_End();

/************************************************************************/
/* 手动启动/关闭一个网络
*/
/************************************************************************/
SCAPI(ScErr) IVE_SDK_StartNetWork(const char* szIP, int nPort, __ConnType enType);
// szServType(=NULL):服务类型(即:服务的设备名,可外部获取在IVE_NetWorkAddr结构体)
SCAPI(ScErr) IVE_SDK_StartNetWorkEx(const char* szIP, int nPort, __ConnType enType, bool bVirtual, const char* szServType);
SCAPI(ScErr) IVE_SDK_EndNetWork(const char* szIP, int nPort, __ConnType enType);

/************************************************************************/
/* 获取所有地址信息
 * IVE_NetWorkAddr* lConfigAddr = NULL;IVE_NET_GetAllNetInfo(&lConfigAddr, &nNumber);
 * 获取成功 pListConfigAddr 需使用IVE_NET_PutAllNetInfo释放
 * 使用方式: lConfigAddr[0] lConfigAddr[1] ... lConfigAddr[*pNumber-1]
 * pNumber 为传入的int类型变量的指针，输出为获取到的数量
*/
/************************************************************************/
SCAPI(ScErr) IVE_NET_GetAllNetInfo(OUT IVE_NetWorkAddr** pListConfigAddr, IN OUT int* pNumber);
SCAPI(void) IVE_NET_PutAllNetInfo(IN IVE_NetWorkAddr* lConfigAddr);

// 获取一个IVE_NetWorkAddr的list,需要用IVE_NET_PutAllVirServList释放
// List使用方式参照IVE_NET_GetAllNetInfo注释
// 注意:会发送同步消息
SCAPI(ScErr) IVE_NET_GetAllVirServ(__ConnHndl hConnTrans, IN OUT IVE_NetWorkAddr** pListVirAddr, IN OUT int* pNum);
SCAPI(void) IVE_NET_PutAllVirServList(IN IVE_NetWorkAddr* lVirAddr);

SCAPI(ScErr) IVE_NET_AddNetInfo(const IVE_NetWorkAddr* pAddrNew);
SCAPI(ScErr) IVE_NET_DelNetInfo(const IVE_NetWorkAddr* pAddrOld);
SCAPI(ScErr) IVE_NET_ModNetInfo(const IVE_NetWorkAddr* pAddrOld, const IVE_NetWorkAddr* pAddrNew);

/************************************************************************/
/* 获取ConnHndl的详细信息
*/
/************************************************************************/
SCAPI(ScErr) IVE_NET_GetConnInfo(__ConnHndl hConn, OUT __ConnInfo* pInfo);

/*******************************************/
/*获取当前可用的连接
 *buffer 用来接收句柄的容器
 *nHndlSize 接收句柄的个数
 *记得使用IVE_NET_PutConnHndls释放内存
 */
/*******************************************/
SCAPI(ScErr) IVE_NET_GetConnHndls(__ConnHndl **pBuffer,int *nHndlSize);

/**
 * 根据开启网络时设置的网络地址参数,查找与对应网络相连的所有连接
 * 其他参照IVE_NET_GetConnHndls
 */
SCAPI(ScErr) IVE_NET_GetConnHndlsByAddr(const char* szIP, int port, __ConnType enType, __ConnHndl **pBuffer,int *nHndlSize);

/**********************************************/
/*释放IVE_GetConnHndls获取的连接列表*/
/**********************************************/
SCAPI(void)  IVE_NET_PutConnHndls(__ConnHndl *buffer);

/************************************************************************/
/* 发送同步消息
 * hConn	连接的句柄
 * szCommand	发送的命令
 * emType	待发送数据pSendNetData的类型
 * pSendNetData	要发送的数据
 * cat		要发送的消息类型
 * szFeedBackCmdBuf	传入256字节的BUF,NULL则不使用,获取反馈数据的命令名
 * ppFeedbackNetData	反馈的数据,为NULL则不使用,使用IVE_NET_ReleaseFeedBackNetData回收该数据
 * pType	反馈数据的类型,为NULL则不使用
 * 返回值	参照IVE_NET_SendMsg介绍
 */
/************************************************************************/
SCAPI(ScErr) IVE_NET_SendSyncMsg(__ConnHndl hConn, const char* szCommand, __NetDataType emType,
							 void *pSendNetData, MsgCategoray cat, OUT char* szFeedBackCmdBuf,OUT void** ppFeedbackNetData, OUT __NetDataType *pType);
SCAPI(ScErr) IVE_NET_SendSyncMsgEx(__ConnHndl hConn, const char* szCommand, __NetDataType emType,
								 void *pSendNetData, MsgCategoray cat,OUT char* szFeedBackCmdBuf,OUT void** ppFeedbackNetData, 
								 OUT __NetDataType *pType, int nTimeOut);
/**
 * 回收IVE_NET_SendSyncMsg反馈数据
 */
SCAPI(ScErr) IVE_NET_ReleaseFeedBackNetData(void* data, __NetDataType emType);

/**
 * 发送异步消息，参数参照IVE_NET_SendSyncMsg
 * NetParamPtr   反馈消息时使用，该参数是收到消息时用来标识数据来源的。
 * SC_ErrNotExist	根据commond没有得到network
 * SC_ErrVersionNotSupport	不支持
 * 
 * SC_ErrRefused	底层通信没有准备好,拒绝服务
 * SC_ErrUnknow	未知错误
 * SC_ErrCreateFailed	创建数据失败
 * SC_ErrNoResources	没有找到该网络连接资源
 */
SCAPI(ScErr) IVE_NET_SendMsg(__ConnHndl hConn, const char* szCommand, __NetDataType emType,
							 void *pSendNetData, MsgCategoray cat);

SCAPI(ScErr) IVE_NET_SendMsgEx(__ConnHndl hConn, const char* szCommand, __NetDataType emType,
	void *pSendNetData, MsgCategoray cat,NetTransferData stNetTransferData);



/**
 * 发送反馈数据
 * 参数参照IVE_NET_SendSyncMsg
 * stNetTransferData	收到消息时所带的网络传导数据,用来标识给谁反馈数据
 */
SCAPI(ScErr) IVE_NET_SendMsgFeedBack(__ConnHndl hConn, const char* szCommand, NetTransferData stNetTransferData, __NetDataType emType,
							 void *pSendNetData, MsgCategoray cat);

/************************************************************************/
/* 注册某个命令的回调函数
*/
/************************************************************************/
///这些接口是旧的为了换库兼容，开发新程序不要调用
// 注册某个命令的回调函数，与所有端口绑定
SCAPI(void) IVE_NET_RegisterCommandCB(const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// 反注册某个命令的回调函数
SCAPI(void) IVE_NET_UnRegisterCommandCB(const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// 注册某个命令的回调函数，与特定端口绑定
SCAPI(void) IVE_NET_RegisterPortCommandCB(int port,const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// 反注册某个命令的回调函数
SCAPI(void) IVE_NET_UnRegisterPortCommandCB(int port,const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
//拦截消息的回调，回调函数返回SC_ErrNotProcessed则继续进行分发，即调用为command注册的回调
SCAPI(void) IVE_NET_RegisterForwordCB(CommandForwardCB CommandCBFunc, void* uiUserData);
///这写是新接口，开发新程序应该优先使用这些接口
// 注册某个命令的回调函数，与所有端口绑定
SCAPI(void) IVE_NET_RegisterCommandCB2(const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// 反注册某个命令的回调函数
SCAPI(void) IVE_NET_UnRegisterCommandCB2(const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// 注册某个命令的回调函数，与特定端口绑定
SCAPI(void) IVE_NET_RegisterPortCommandCB2(int port,const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// 反注册某个命令的回调函数
SCAPI(void) IVE_NET_UnRegisterPortCommandCB2(int port,const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
//拦截消息的回调，回调函数返回SC_ErrNotProcessed则继续进行分发，即调用为command注册的回调
SCAPI(void) IVE_NET_RegisterForwordCB2(CommandForwardCB CommandCBFunc, void* uiUserData);



SCAPI(void) IVE_Logger_AddLog(__LogLevel emlevel, const char* szFileName, const char* szSection, const char* szContentFormat, ... );

//日志最大长度为2048字节
SCAPI(ScErr) IVE_Logger_AddLogTo(__ConnHndl hConn, __LogLevel emlevel, const char* szFileName, const char* szSection, const char* szContentFormat, ... );

SCAPI(ScErr) IVE_Logger_AddAlarmTo(__ConnHndl hConn, 
	const char* szServiceType, 
	__AlarmLevel emlevel, 
	const char* szSection, 
	const char* szContentFormat, ... );

/************************************************************************/
/* 发送同步消息
 * szSource	 产生报警的设备ID
 * szTarget	报警指向的设备ID
 * emlevel		报警级别
 * uiAlarmType		报警类型
 * szContentFormat	报警内容
 */
/************************************************************************/
SCAPI(ScErr) IVE_Logger_AddAlarm(const char* szSource, 
	const char* szTarget, 
	__AlarmLevel emlevel, 
	unsigned int uiAlarmType, 
	const char* szContentFormat, ... );

SCAPI(ScErr) IVE_Logger_CancelAlarm(const char* szTarget, 
	unsigned int uiAlarmType);

// 获取指定年月日下所有的日志文件的名称集合,中间以英文分号";"结尾,如果传入pPathBuf大小nSizeBuf不够大,则获取失败
SCAPI(ScErr) IVE_Logger_GetLog(ScSystemTime tmLog, OUT char* pPathBuf, IN int nSizeBuf);

SCAPI(void) IVE_Logger_RegistLogCallBack(ScLoggerCallBack funCB);
SCAPI(void) IVE_Logger_RegistLogCallBackEx(ScLoggerCallBack funCB, void* uiUserData);

// 设置本地的日志级别对应的功能(记录本地、发送网络)到配置文件中
// 返回：{true:设置成功; false:设置失败}
SCAPI(bool) IVE_SetLogType(__LogLevel emLevel, bool bLogFile, bool bLogNet);
SCAPI(bool) IVE_SetLogTypeEx(__LogLevel emLevel, bool bLogFile, bool bLogNet, bool bLogScreen);
// 设置日志选项：
// "printscreen":1开启屏幕日志，默认是关闭的，一般用法是在debug版本开启
SCAPI(bool) IVE_SetLogOption(const char* optname,int optvalue);

/************************************************************************/
//功能：注册一项
//参数：
//		szWndName|状态窗口名称
//			szKey|状态窗口中的一个属性名称
//			   cb|状态回调函数
//	   uiUserData|附加参数
//返回值： 成功返回SC_ErrSuccess
//说明：
/************************************************************************/
SCAPI(ScErr) IVE_Status_RegItemSend(
							 const char* szWndName,
							 const char* szKey,
							 ScStatusSendCallBack cb,
							 void* uiUserData);
/************************************************************************/
//功能：反注册一项
//参数：
//			   cb|状态回调函数
//	   uiUserData|附加参数
//返回值： 成功返回SC_ErrSuccess
//说明：
/************************************************************************/
SCAPI(ScErr) IVE_Status_UnRegItemSend(
							   const char* szWndName,
							   const char* szKey,
							   ScStatusSendCallBack cb,
							   void* uiUserData);
/************************************************************************/
/* 注册接收回调函数
	@param uiUserData 回调时附加参数
*/
/************************************************************************/
SCAPI(ScErr) IVE_Status_RegItemRecv(ScStatusRecvCallBack cb, void* uiUserData);

/************************************************************************/
//功能：在相机端设置状态值，提供格式化字符串的方式。
//参数：
//		szWndName|状态窗口名称
//			szKey|状态窗口中的一个属性名称
//返回值： 成功返回SC_ErrSuccess
//说明：主动发送时pParam为NULL
/************************************************************************/
SCAPI(ScErr) IVE_Status_SetValueFormat(__ConnHndl hConn,
									const char* szWndName,
									const char* szKey,
									const char* szFormat,
									...		//状态项数据
									);


SCAPI(ScErr) IVE_Status_RefreshItem(const char* szWndName);


// 服务端初始化配置句柄，HSCConfig
SCAPI(ScErr) IVE_Config_RegConfig(void *hCfg, ScConfigEventCallBack cb, void* uiUserData);
// 客户端调用，设置指定的配置项值到指定连接
SCAPI(ScErr) IVE_Config_SetConfigItem(__ConnHndl hConn,
								   const char* szCfgKey,
								   const char* szFormat,
								   ...		//配置项数据
								   );

// SCAPI(ScErr) IVE_Config_RegConfigRecv(ScConfigRecvCallBack cb, void* uiUserData);
SCAPI(ScErr) IVE_Config_GetConfigStream(__ConnHndl hConn, char **szValStream, char **szAttStream);
SCAPI(ScErr) IVE_Config_DestoryConfigStream(char *szValStream, char *szAttStream);
SCAPI(ScErr) IVE_Config_SetConfigStream(__ConnHndl hConn, const char *szValStream, const char *szAttStream);


#endif
