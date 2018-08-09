#ifndef SC_ERR_H
#define SC_ERR_H

/** @file ScErr.h
*	@brief ScErr错误码定义
*/

/** 错误信息标识 */
typedef enum
{
	// 通用
	SC_ErrSuccess = 0 ,		//成功
	SC_ErrNullReturn = 1,		//空返回
	SC_ErrParamerErr = 2,		//参数错误
	SC_ErrNotExist = 4,		    //不存在
	SC_ErrTypeErr = 5,			//类型错误
	SC_ErrInfoTooLong = 7,		//信息太长
	SC_ErrCreateFailed = 9,		//创建失败
	SC_ErrLogicError = 11,		//逻辑错误
	SC_ErrUnknow = 13,			//未知错误
	SC_ErrLockAuthen = 16,      //被锁定
	SC_ErrLockPasswd = 17,      //密码被锁定
	SC_ErrFULL = 21,			 //满了
	Sc_ErrEmpty = 23,			 //空的
	SC_ErrYes = 25,//是
	SC_ErrNo = 26,   //不是
	SC_ErrDataTransErr = 28, //数据转换错误
	SC_ErrUserNamePWDWrong = 31,  //用户名密码失败
	SC_ErrException = 36,			//捕获到未知异常
	SC_ErrNotImplementation=37,		//未实现，函数未真正实现时应该返回该值
	SC_ErrNotProcessed = 39,		// 未处理

	// 图像
	SC_Err_MergJpg_ReadJpgHearderError = 1000, //读取Jpeg头失败 songj
	SC_Err_MergJpg_ReadJpgTableError   =1001, //量化表, huffman表不一致
	SC_ErrFreeFrameFaile = 15,    
	SC_ErrGetFrameFromMSFaile = 14,	//
	SC_ErrCantConnectMediaSource = 12,	//无法连接视频源

	// 系统
	SC_ErrSysVersionNotSupport = 1300, 
	SC_ErrVersionNotSupport = 10,	//不支持的版本
	SC_UnInit = 33,				//没有初始化

	// 内存【1500-1599】
	SC_ErrMemAllocFailed = 1500,			// 内存分配失败
	SC_ErrMemNotEnough  = 24,			// 内存不足
	SC_ErrMemOverflow = 1502,			// 内存溢出
	SC_ErrMemNotAccessable = 1504,	// 内存不可访问
	SC_ErrMemNotInitialized = 1506,		// 内存未初始化
	SC_ErrMemAlreadyFreed = 1508,		// 内存已释放
	
	// 网络【2000-2299】
	SC_ErrNetIllegalAddress = 2000,			// 非法的网络地址
	SC_ErrNetUnknownProtocol = 2002,		// 未知的网络协议
	SC_ErrNetInvalidSocket = 2004,			// Socket失效
	SC_ErrNetSendFailed = 2006,				// 发送失败
	SC_ErrNetSendTimeOut = 2008,			// 发送超时
	SC_ErrNetSendBufferFull = 2010,			// 发送缓冲区满
	SC_ErrNetRecvIllegalData = 2012,		// 接受到非法数据
	SC_ErrNetConnectionClosedByPeer = 2014,		// 连接被远端关闭
	SC_ErrNetTooMuchConnection = 2016,				// 连接过多

	SC_ErrNetNotConnected = 2038,		// 未连接

	SC_ErrNetCreateMsgFailed = 2050,		// 创建消息失败
	SC_ErrNetParserMsgFailed = 2052,		// 解析消息失败
	SC_ErrNetMsgDestoryed = 2054,			// 消息已销毁

	// 数据库【2300-2499】
	SC_ErrDBOutOfService = 2300,		// 数据库服务未开启
	SC_ErrDBLoginFailed = 2302,			// 登录数据库失败
	SC_ErrDBUserNotExist = 2304,		// 用户不存在
	SC_ErrDBDataBaseNotExist = 2306,	// 数据库不存在
	SC_ErrDBTableNotExist = 2308,		// 数据表不存在
	SC_ErrDBConnectionClosed = 2310,	// 连接关闭
	SC_ErrDBIllegalSql = 2312,				// 非法的SQL
	SC_ErrDBIllegalScript = 2314,			// 非法的SQL脚本
	SC_ErrDBExecuteSqlFailed = 2316,	// 执行SQL失败
	SC_ErrDBNoData = 2318,				// 无数据

	// 文件、端口、目录【2500-2699】
	SC_ErrFileNotExist = 2500,				// 文件不存在
	SC_ErrFileCreateFailed = 2502,		// 创建文件失败
	SC_ErrFileOpenFailed = 2504,			// 打开文件失败
	SC_ErrFileReadFailed = 2506,			// 读取文件失败
	SC_ErrFileWriteFailed = 2508,			// 写入文件失败
	SC_ErrFileNoReadAuthorization = 2510,		// 无读权限
	SC_ErrFileNoWriteAuthorization = 2512,	// 无写权限
	SC_ErrFileZeroKB = 2514,				// 文件为0KB
	SC_ErrFileTooLarge = 2516,			// 文件过大
	SC_ErrFileTooSmall = 2518,			// 文件过小
	SC_ErrFileErrorEncoding = 2520,		// 文件编码错误
	SC_ErrFileLocked = 2522,				// 文件被锁定（被占用）
	SC_ErrFileAlreadyExist = 2524,		// 文件已存在
	SC_ErrFileNameIsTooLong = 2526,	// 文件名过长

	SC_ErrPathNotExist = 2600,			// 路径不存在
	SC_ErrPathAlreadyExist = 2602,		// 路径已存在
	SC_ErrPathNotEmpty = 2604,		// 路径不为空（路径下有文件）
	SC_ErrPathIsTooLong = 2606,		// 路径过长
	SC_ErrPathIsIllegal = 2608,			// 路径非法

	
	// 服务【2700-2799】
	SC_ErrServiceOutOfService = 2700,		// 服务未开启
	SC_ErrServiceNotLogin = 2702,			// 未登录服务
	SC_ErrServiceLoginFailed = 2704,		// 登录失败
	SC_ErrServiceUserNotExist = 2706,		// 用户不存在
	SC_ErrServiceNotSupported = 2708,	// 不支持的服务
	SC_ErrServiceRefused = 2710,			// 请求被拒绝
	SC_ErrServiceNoPrivilege = 2712,		// 无服务权限
	SC_ErrServicePrivilegeOccupied = 2714,		// 权限被抢占
	SC_ErrServiceTimeOut = 2716,			// 服务超时
	SC_ErrServiceNoResource = 2718,		// 无服务资源
	SC_ErrServiceTryingOccupy = 2720, 	// 尝试抢占

	// Legacy，尽量使用分类错误码，避免使用Legacy错误码
	SC_ErrRefused = 22,			 //拒绝
	SC_ErrMemoryAlloc = 8,		//内存分配失败s
	SC_ErrPathNotFound = 3,		//访问路径不存在
	SC_ErrSendErr = 19,  //发送错误
	SC_ErrDataBaseErr = 34,            //数据库错误，连接或操作错误
	SC_ErrUserNoPrivilege = 32,	  //没有权限
	SC_ErrNoResources = 30,  //没有需要的资源
	SC_ErrDataOverflow = 29,
	SC_ErrReceiveDataErr = 27,//接受数据错误
	SC_ErrTimeOut = 18, //超时
	SC_ErrAlreadyExisted = 20,    //已经存在
	SC_ErrOpenFileFailed = 6,	//打开文件失败
	SC_ErrNotConnected = 38,		//没有建立连接
	SC_ErrPrivilegeOccupied = 35,  //权限被占用
	SC_ErrOpen = 39,					//打开失败
	SC_ErrRead = 40,					//读取失败
	SC_ErrNoUsefulData = 41,			//没有可用数据

}ScErr;

#define SC_ErrNodeNotExist SC_ErrNotExist


#endif 