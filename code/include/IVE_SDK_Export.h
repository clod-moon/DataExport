/************************************************************************/
/* �������ӵĲ���Ϊʹ��__ConnHndl���
*/
/************************************************************************/
#ifndef IVE_SDK_EXPORT_H
#define IVE_SDK_EXPORT_H
#include "IContainerBase.h"
#include "CommonObjExport.h"
#include "IVE_Const.h"



/******************************************/
/*��ʼ��IVE
	nMaxFolderNum:��־�ļ����޶�����
	nMaxFileSize:��־�ļ����byte
	szFilePath:��־�ļ�·��
*/
/******************************************/
SCAPI(BOOL) IVE_SDK_Init(int nMaxSaveFileDay, int nMaxFileSize, const char* szFilePath);

/******************************************/
/*����ʼ��IVE*/
/******************************************/
SCAPI(void) IVE_SDK_UnInit();

SCAPI(BOOL) IVE_SDK_Start();
SCAPI(void) IVE_SDK_End();

/************************************************************************/
/* �ֶ�����/�ر�һ������
*/
/************************************************************************/
SCAPI(ScErr) IVE_SDK_StartNetWork(const char* szIP, int nPort, __ConnType enType);
// szServType(=NULL):��������(��:������豸��,���ⲿ��ȡ��IVE_NetWorkAddr�ṹ��)
SCAPI(ScErr) IVE_SDK_StartNetWorkEx(const char* szIP, int nPort, __ConnType enType, bool bVirtual, const char* szServType);
SCAPI(ScErr) IVE_SDK_EndNetWork(const char* szIP, int nPort, __ConnType enType);

/************************************************************************/
/* ��ȡ���е�ַ��Ϣ
 * IVE_NetWorkAddr* lConfigAddr = NULL;IVE_NET_GetAllNetInfo(&lConfigAddr, &nNumber);
 * ��ȡ�ɹ� pListConfigAddr ��ʹ��IVE_NET_PutAllNetInfo�ͷ�
 * ʹ�÷�ʽ: lConfigAddr[0] lConfigAddr[1] ... lConfigAddr[*pNumber-1]
 * pNumber Ϊ�����int���ͱ�����ָ�룬���Ϊ��ȡ��������
*/
/************************************************************************/
SCAPI(ScErr) IVE_NET_GetAllNetInfo(OUT IVE_NetWorkAddr** pListConfigAddr, IN OUT int* pNumber);
SCAPI(void) IVE_NET_PutAllNetInfo(IN IVE_NetWorkAddr* lConfigAddr);

// ��ȡһ��IVE_NetWorkAddr��list,��Ҫ��IVE_NET_PutAllVirServList�ͷ�
// Listʹ�÷�ʽ����IVE_NET_GetAllNetInfoע��
// ע��:�ᷢ��ͬ����Ϣ
SCAPI(ScErr) IVE_NET_GetAllVirServ(__ConnHndl hConnTrans, IN OUT IVE_NetWorkAddr** pListVirAddr, IN OUT int* pNum);
SCAPI(void) IVE_NET_PutAllVirServList(IN IVE_NetWorkAddr* lVirAddr);

SCAPI(ScErr) IVE_NET_AddNetInfo(const IVE_NetWorkAddr* pAddrNew);
SCAPI(ScErr) IVE_NET_DelNetInfo(const IVE_NetWorkAddr* pAddrOld);
SCAPI(ScErr) IVE_NET_ModNetInfo(const IVE_NetWorkAddr* pAddrOld, const IVE_NetWorkAddr* pAddrNew);

/************************************************************************/
/* ��ȡConnHndl����ϸ��Ϣ
*/
/************************************************************************/
SCAPI(ScErr) IVE_NET_GetConnInfo(__ConnHndl hConn, OUT __ConnInfo* pInfo);

/*******************************************/
/*��ȡ��ǰ���õ�����
 *buffer �������վ��������
 *nHndlSize ���վ���ĸ���
 *�ǵ�ʹ��IVE_NET_PutConnHndls�ͷ��ڴ�
 */
/*******************************************/
SCAPI(ScErr) IVE_NET_GetConnHndls(__ConnHndl **pBuffer,int *nHndlSize);

/**
 * ���ݿ�������ʱ���õ������ַ����,�������Ӧ������������������
 * ��������IVE_NET_GetConnHndls
 */
SCAPI(ScErr) IVE_NET_GetConnHndlsByAddr(const char* szIP, int port, __ConnType enType, __ConnHndl **pBuffer,int *nHndlSize);

/**********************************************/
/*�ͷ�IVE_GetConnHndls��ȡ�������б�*/
/**********************************************/
SCAPI(void)  IVE_NET_PutConnHndls(__ConnHndl *buffer);

/************************************************************************/
/* ����ͬ����Ϣ
 * hConn	���ӵľ��
 * szCommand	���͵�����
 * emType	����������pSendNetData������
 * pSendNetData	Ҫ���͵�����
 * cat		Ҫ���͵���Ϣ����
 * szFeedBackCmdBuf	����256�ֽڵ�BUF,NULL��ʹ��,��ȡ�������ݵ�������
 * ppFeedbackNetData	����������,ΪNULL��ʹ��,ʹ��IVE_NET_ReleaseFeedBackNetData���ո�����
 * pType	�������ݵ�����,ΪNULL��ʹ��
 * ����ֵ	����IVE_NET_SendMsg����
 */
/************************************************************************/
SCAPI(ScErr) IVE_NET_SendSyncMsg(__ConnHndl hConn, const char* szCommand, __NetDataType emType,
							 void *pSendNetData, MsgCategoray cat, OUT char* szFeedBackCmdBuf,OUT void** ppFeedbackNetData, OUT __NetDataType *pType);
SCAPI(ScErr) IVE_NET_SendSyncMsgEx(__ConnHndl hConn, const char* szCommand, __NetDataType emType,
								 void *pSendNetData, MsgCategoray cat,OUT char* szFeedBackCmdBuf,OUT void** ppFeedbackNetData, 
								 OUT __NetDataType *pType, int nTimeOut);
/**
 * ����IVE_NET_SendSyncMsg��������
 */
SCAPI(ScErr) IVE_NET_ReleaseFeedBackNetData(void* data, __NetDataType emType);

/**
 * �����첽��Ϣ����������IVE_NET_SendSyncMsg
 * NetParamPtr   ������Ϣʱʹ�ã��ò������յ���Ϣʱ������ʶ������Դ�ġ�
 * SC_ErrNotExist	����commondû�еõ�network
 * SC_ErrVersionNotSupport	��֧��
 * 
 * SC_ErrRefused	�ײ�ͨ��û��׼����,�ܾ�����
 * SC_ErrUnknow	δ֪����
 * SC_ErrCreateFailed	��������ʧ��
 * SC_ErrNoResources	û���ҵ�������������Դ
 */
SCAPI(ScErr) IVE_NET_SendMsg(__ConnHndl hConn, const char* szCommand, __NetDataType emType,
							 void *pSendNetData, MsgCategoray cat);

SCAPI(ScErr) IVE_NET_SendMsgEx(__ConnHndl hConn, const char* szCommand, __NetDataType emType,
	void *pSendNetData, MsgCategoray cat,NetTransferData stNetTransferData);



/**
 * ���ͷ�������
 * ��������IVE_NET_SendSyncMsg
 * stNetTransferData	�յ���Ϣʱ���������紫������,������ʶ��˭��������
 */
SCAPI(ScErr) IVE_NET_SendMsgFeedBack(__ConnHndl hConn, const char* szCommand, NetTransferData stNetTransferData, __NetDataType emType,
							 void *pSendNetData, MsgCategoray cat);

/************************************************************************/
/* ע��ĳ������Ļص�����
*/
/************************************************************************/
///��Щ�ӿ��Ǿɵ�Ϊ�˻�����ݣ������³���Ҫ����
// ע��ĳ������Ļص������������ж˿ڰ�
SCAPI(void) IVE_NET_RegisterCommandCB(const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// ��ע��ĳ������Ļص�����
SCAPI(void) IVE_NET_UnRegisterCommandCB(const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// ע��ĳ������Ļص����������ض��˿ڰ�
SCAPI(void) IVE_NET_RegisterPortCommandCB(int port,const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// ��ע��ĳ������Ļص�����
SCAPI(void) IVE_NET_UnRegisterPortCommandCB(int port,const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
//������Ϣ�Ļص����ص���������SC_ErrNotProcessed��������зַ���������Ϊcommandע��Ļص�
SCAPI(void) IVE_NET_RegisterForwordCB(CommandForwardCB CommandCBFunc, void* uiUserData);
///��д���½ӿڣ������³���Ӧ������ʹ����Щ�ӿ�
// ע��ĳ������Ļص������������ж˿ڰ�
SCAPI(void) IVE_NET_RegisterCommandCB2(const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// ��ע��ĳ������Ļص�����
SCAPI(void) IVE_NET_UnRegisterCommandCB2(const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// ע��ĳ������Ļص����������ض��˿ڰ�
SCAPI(void) IVE_NET_RegisterPortCommandCB2(int port,const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
// ��ע��ĳ������Ļص�����
SCAPI(void) IVE_NET_UnRegisterPortCommandCB2(int port,const char* szCommand,CommandCB CommandCBFunc, void* uiUserData);
//������Ϣ�Ļص����ص���������SC_ErrNotProcessed��������зַ���������Ϊcommandע��Ļص�
SCAPI(void) IVE_NET_RegisterForwordCB2(CommandForwardCB CommandCBFunc, void* uiUserData);



SCAPI(void) IVE_Logger_AddLog(__LogLevel emlevel, const char* szFileName, const char* szSection, const char* szContentFormat, ... );

//��־��󳤶�Ϊ2048�ֽ�
SCAPI(ScErr) IVE_Logger_AddLogTo(__ConnHndl hConn, __LogLevel emlevel, const char* szFileName, const char* szSection, const char* szContentFormat, ... );

SCAPI(ScErr) IVE_Logger_AddAlarmTo(__ConnHndl hConn, 
	const char* szServiceType, 
	__AlarmLevel emlevel, 
	const char* szSection, 
	const char* szContentFormat, ... );

/************************************************************************/
/* ����ͬ����Ϣ
 * szSource	 �����������豸ID
 * szTarget	����ָ����豸ID
 * emlevel		��������
 * uiAlarmType		��������
 * szContentFormat	��������
 */
/************************************************************************/
SCAPI(ScErr) IVE_Logger_AddAlarm(const char* szSource, 
	const char* szTarget, 
	__AlarmLevel emlevel, 
	unsigned int uiAlarmType, 
	const char* szContentFormat, ... );

SCAPI(ScErr) IVE_Logger_CancelAlarm(const char* szTarget, 
	unsigned int uiAlarmType);

// ��ȡָ�������������е���־�ļ������Ƽ���,�м���Ӣ�ķֺ�";"��β,�������pPathBuf��СnSizeBuf������,���ȡʧ��
SCAPI(ScErr) IVE_Logger_GetLog(ScSystemTime tmLog, OUT char* pPathBuf, IN int nSizeBuf);

SCAPI(void) IVE_Logger_RegistLogCallBack(ScLoggerCallBack funCB);
SCAPI(void) IVE_Logger_RegistLogCallBackEx(ScLoggerCallBack funCB, void* uiUserData);

// ���ñ��ص���־�����Ӧ�Ĺ���(��¼���ء���������)�������ļ���
// ���أ�{true:���óɹ�; false:����ʧ��}
SCAPI(bool) IVE_SetLogType(__LogLevel emLevel, bool bLogFile, bool bLogNet);
SCAPI(bool) IVE_SetLogTypeEx(__LogLevel emLevel, bool bLogFile, bool bLogNet, bool bLogScreen);
// ������־ѡ�
// "printscreen":1������Ļ��־��Ĭ���ǹرյģ�һ���÷�����debug�汾����
SCAPI(bool) IVE_SetLogOption(const char* optname,int optvalue);

/************************************************************************/
//���ܣ�ע��һ��
//������
//		szWndName|״̬��������
//			szKey|״̬�����е�һ����������
//			   cb|״̬�ص�����
//	   uiUserData|���Ӳ���
//����ֵ�� �ɹ�����SC_ErrSuccess
//˵����
/************************************************************************/
SCAPI(ScErr) IVE_Status_RegItemSend(
							 const char* szWndName,
							 const char* szKey,
							 ScStatusSendCallBack cb,
							 void* uiUserData);
/************************************************************************/
//���ܣ���ע��һ��
//������
//			   cb|״̬�ص�����
//	   uiUserData|���Ӳ���
//����ֵ�� �ɹ�����SC_ErrSuccess
//˵����
/************************************************************************/
SCAPI(ScErr) IVE_Status_UnRegItemSend(
							   const char* szWndName,
							   const char* szKey,
							   ScStatusSendCallBack cb,
							   void* uiUserData);
/************************************************************************/
/* ע����ջص�����
	@param uiUserData �ص�ʱ���Ӳ���
*/
/************************************************************************/
SCAPI(ScErr) IVE_Status_RegItemRecv(ScStatusRecvCallBack cb, void* uiUserData);

/************************************************************************/
//���ܣ������������״ֵ̬���ṩ��ʽ���ַ����ķ�ʽ��
//������
//		szWndName|״̬��������
//			szKey|״̬�����е�һ����������
//����ֵ�� �ɹ�����SC_ErrSuccess
//˵������������ʱpParamΪNULL
/************************************************************************/
SCAPI(ScErr) IVE_Status_SetValueFormat(__ConnHndl hConn,
									const char* szWndName,
									const char* szKey,
									const char* szFormat,
									...		//״̬������
									);


SCAPI(ScErr) IVE_Status_RefreshItem(const char* szWndName);


// ����˳�ʼ�����þ����HSCConfig
SCAPI(ScErr) IVE_Config_RegConfig(void *hCfg, ScConfigEventCallBack cb, void* uiUserData);
// �ͻ��˵��ã�����ָ����������ֵ��ָ������
SCAPI(ScErr) IVE_Config_SetConfigItem(__ConnHndl hConn,
								   const char* szCfgKey,
								   const char* szFormat,
								   ...		//����������
								   );

// SCAPI(ScErr) IVE_Config_RegConfigRecv(ScConfigRecvCallBack cb, void* uiUserData);
SCAPI(ScErr) IVE_Config_GetConfigStream(__ConnHndl hConn, char **szValStream, char **szAttStream);
SCAPI(ScErr) IVE_Config_DestoryConfigStream(char *szValStream, char *szAttStream);
SCAPI(ScErr) IVE_Config_SetConfigStream(__ConnHndl hConn, const char *szValStream, const char *szAttStream);


#endif
