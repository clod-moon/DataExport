#pragma once
//////////////////////////////////////////////////////////////////////////
// IVE_CORE 的工具接口
//////////////////////////////////////////////////////////////////////////
#include "IVE_Const.h"

//////////////////////////////////////////////////////////////////////////

// 问询方式上传下载：
// 会询问对方 上传下载的相关路径信息
// 自动方式上传下载：
// 会自动根据注册的路径 查找上传下载相关路径信息


////////////////问询模式//////////////////////////////////////////////////////////
// 注册目录问询函数
SCAPI(ScErr) IVE_NETTool_AskModeRegPathCB(FuncIVE_AskModeSetPathCB funcSetUpLoadPath, void* pRegister);

// 注册上传下载中的事件通知函数
SCAPI(ScErr) IVE_NETTool_AskModeRegEventCB(FuncIVE_AskModeEventCB funcEvent, void* pRegister);

// 服务端同步发送接口
SCAPI(ScErr) IVE_NETTool_AskModeUpload(__ConnHndl hConn, unsigned int nProgressBefore, unsigned int nProgressSend, unsigned int nUpLoadID, const char* szPathArr[], int nTimeOut);

////////////////自动模式//////////////////////////////////////////////////////////
// 注册上传下载自动查找路径
SCAPI(ScErr) IVE_NETTool_AutoModeSetConfigFile(const char* szIniPath);

// 自动（静默方式）下载
SCAPI(ScErr) IVE_NETTool_AutoModeDownload(__ConnHndl hConnSrc, const char* szKeyName, const char* szDestPath, int nTimeOut);

// 自动（静默方式）上传
SCAPI(ScErr) IVE_NETTool_AutoModeUpload(__ConnHndl hConnDest, const char* szKeyName, const char* szSrcPath, int nTimeOut);


