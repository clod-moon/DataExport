#pragma once
//////////////////////////////////////////////////////////////////////////
// IVE_CORE �Ĺ��߽ӿ�
//////////////////////////////////////////////////////////////////////////
#include "IVE_Const.h"

//////////////////////////////////////////////////////////////////////////

// ��ѯ��ʽ�ϴ����أ�
// ��ѯ�ʶԷ� �ϴ����ص����·����Ϣ
// �Զ���ʽ�ϴ����أ�
// ���Զ�����ע���·�� �����ϴ��������·����Ϣ


////////////////��ѯģʽ//////////////////////////////////////////////////////////
// ע��Ŀ¼��ѯ����
SCAPI(ScErr) IVE_NETTool_AskModeRegPathCB(FuncIVE_AskModeSetPathCB funcSetUpLoadPath, void* pRegister);

// ע���ϴ������е��¼�֪ͨ����
SCAPI(ScErr) IVE_NETTool_AskModeRegEventCB(FuncIVE_AskModeEventCB funcEvent, void* pRegister);

// �����ͬ�����ͽӿ�
SCAPI(ScErr) IVE_NETTool_AskModeUpload(__ConnHndl hConn, unsigned int nProgressBefore, unsigned int nProgressSend, unsigned int nUpLoadID, const char* szPathArr[], int nTimeOut);

////////////////�Զ�ģʽ//////////////////////////////////////////////////////////
// ע���ϴ������Զ�����·��
SCAPI(ScErr) IVE_NETTool_AutoModeSetConfigFile(const char* szIniPath);

// �Զ�����Ĭ��ʽ������
SCAPI(ScErr) IVE_NETTool_AutoModeDownload(__ConnHndl hConnSrc, const char* szKeyName, const char* szDestPath, int nTimeOut);

// �Զ�����Ĭ��ʽ���ϴ�
SCAPI(ScErr) IVE_NETTool_AutoModeUpload(__ConnHndl hConnDest, const char* szKeyName, const char* szSrcPath, int nTimeOut);


