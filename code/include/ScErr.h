#ifndef SC_ERR_H
#define SC_ERR_H

/** @file ScErr.h
*	@brief ScErr�����붨��
*/

/** ������Ϣ��ʶ */
typedef enum
{
	// ͨ��
	SC_ErrSuccess = 0 ,		//�ɹ�
	SC_ErrNullReturn = 1,		//�շ���
	SC_ErrParamerErr = 2,		//��������
	SC_ErrNotExist = 4,		    //������
	SC_ErrTypeErr = 5,			//���ʹ���
	SC_ErrInfoTooLong = 7,		//��Ϣ̫��
	SC_ErrCreateFailed = 9,		//����ʧ��
	SC_ErrLogicError = 11,		//�߼�����
	SC_ErrUnknow = 13,			//δ֪����
	SC_ErrLockAuthen = 16,      //������
	SC_ErrLockPasswd = 17,      //���뱻����
	SC_ErrFULL = 21,			 //����
	Sc_ErrEmpty = 23,			 //�յ�
	SC_ErrYes = 25,//��
	SC_ErrNo = 26,   //����
	SC_ErrDataTransErr = 28, //����ת������
	SC_ErrUserNamePWDWrong = 31,  //�û�������ʧ��
	SC_ErrException = 36,			//����δ֪�쳣
	SC_ErrNotImplementation=37,		//δʵ�֣�����δ����ʵ��ʱӦ�÷��ظ�ֵ
	SC_ErrNotProcessed = 39,		// δ����

	// ͼ��
	SC_Err_MergJpg_ReadJpgHearderError = 1000, //��ȡJpegͷʧ�� songj
	SC_Err_MergJpg_ReadJpgTableError   =1001, //������, huffman��һ��
	SC_ErrFreeFrameFaile = 15,    
	SC_ErrGetFrameFromMSFaile = 14,	//
	SC_ErrCantConnectMediaSource = 12,	//�޷�������ƵԴ

	// ϵͳ
	SC_ErrSysVersionNotSupport = 1300, 
	SC_ErrVersionNotSupport = 10,	//��֧�ֵİ汾
	SC_UnInit = 33,				//û�г�ʼ��

	// �ڴ桾1500-1599��
	SC_ErrMemAllocFailed = 1500,			// �ڴ����ʧ��
	SC_ErrMemNotEnough  = 24,			// �ڴ治��
	SC_ErrMemOverflow = 1502,			// �ڴ����
	SC_ErrMemNotAccessable = 1504,	// �ڴ治�ɷ���
	SC_ErrMemNotInitialized = 1506,		// �ڴ�δ��ʼ��
	SC_ErrMemAlreadyFreed = 1508,		// �ڴ����ͷ�
	
	// ���硾2000-2299��
	SC_ErrNetIllegalAddress = 2000,			// �Ƿ��������ַ
	SC_ErrNetUnknownProtocol = 2002,		// δ֪������Э��
	SC_ErrNetInvalidSocket = 2004,			// SocketʧЧ
	SC_ErrNetSendFailed = 2006,				// ����ʧ��
	SC_ErrNetSendTimeOut = 2008,			// ���ͳ�ʱ
	SC_ErrNetSendBufferFull = 2010,			// ���ͻ�������
	SC_ErrNetRecvIllegalData = 2012,		// ���ܵ��Ƿ�����
	SC_ErrNetConnectionClosedByPeer = 2014,		// ���ӱ�Զ�˹ر�
	SC_ErrNetTooMuchConnection = 2016,				// ���ӹ���

	SC_ErrNetNotConnected = 2038,		// δ����

	SC_ErrNetCreateMsgFailed = 2050,		// ������Ϣʧ��
	SC_ErrNetParserMsgFailed = 2052,		// ������Ϣʧ��
	SC_ErrNetMsgDestoryed = 2054,			// ��Ϣ������

	// ���ݿ⡾2300-2499��
	SC_ErrDBOutOfService = 2300,		// ���ݿ����δ����
	SC_ErrDBLoginFailed = 2302,			// ��¼���ݿ�ʧ��
	SC_ErrDBUserNotExist = 2304,		// �û�������
	SC_ErrDBDataBaseNotExist = 2306,	// ���ݿⲻ����
	SC_ErrDBTableNotExist = 2308,		// ���ݱ�����
	SC_ErrDBConnectionClosed = 2310,	// ���ӹر�
	SC_ErrDBIllegalSql = 2312,				// �Ƿ���SQL
	SC_ErrDBIllegalScript = 2314,			// �Ƿ���SQL�ű�
	SC_ErrDBExecuteSqlFailed = 2316,	// ִ��SQLʧ��
	SC_ErrDBNoData = 2318,				// ������

	// �ļ����˿ڡ�Ŀ¼��2500-2699��
	SC_ErrFileNotExist = 2500,				// �ļ�������
	SC_ErrFileCreateFailed = 2502,		// �����ļ�ʧ��
	SC_ErrFileOpenFailed = 2504,			// ���ļ�ʧ��
	SC_ErrFileReadFailed = 2506,			// ��ȡ�ļ�ʧ��
	SC_ErrFileWriteFailed = 2508,			// д���ļ�ʧ��
	SC_ErrFileNoReadAuthorization = 2510,		// �޶�Ȩ��
	SC_ErrFileNoWriteAuthorization = 2512,	// ��дȨ��
	SC_ErrFileZeroKB = 2514,				// �ļ�Ϊ0KB
	SC_ErrFileTooLarge = 2516,			// �ļ�����
	SC_ErrFileTooSmall = 2518,			// �ļ���С
	SC_ErrFileErrorEncoding = 2520,		// �ļ��������
	SC_ErrFileLocked = 2522,				// �ļ�����������ռ�ã�
	SC_ErrFileAlreadyExist = 2524,		// �ļ��Ѵ���
	SC_ErrFileNameIsTooLong = 2526,	// �ļ�������

	SC_ErrPathNotExist = 2600,			// ·��������
	SC_ErrPathAlreadyExist = 2602,		// ·���Ѵ���
	SC_ErrPathNotEmpty = 2604,		// ·����Ϊ�գ�·�������ļ���
	SC_ErrPathIsTooLong = 2606,		// ·������
	SC_ErrPathIsIllegal = 2608,			// ·���Ƿ�

	
	// ����2700-2799��
	SC_ErrServiceOutOfService = 2700,		// ����δ����
	SC_ErrServiceNotLogin = 2702,			// δ��¼����
	SC_ErrServiceLoginFailed = 2704,		// ��¼ʧ��
	SC_ErrServiceUserNotExist = 2706,		// �û�������
	SC_ErrServiceNotSupported = 2708,	// ��֧�ֵķ���
	SC_ErrServiceRefused = 2710,			// ���󱻾ܾ�
	SC_ErrServiceNoPrivilege = 2712,		// �޷���Ȩ��
	SC_ErrServicePrivilegeOccupied = 2714,		// Ȩ�ޱ���ռ
	SC_ErrServiceTimeOut = 2716,			// ����ʱ
	SC_ErrServiceNoResource = 2718,		// �޷�����Դ
	SC_ErrServiceTryingOccupy = 2720, 	// ������ռ

	// Legacy������ʹ�÷�������룬����ʹ��Legacy������
	SC_ErrRefused = 22,			 //�ܾ�
	SC_ErrMemoryAlloc = 8,		//�ڴ����ʧ��s
	SC_ErrPathNotFound = 3,		//����·��������
	SC_ErrSendErr = 19,  //���ʹ���
	SC_ErrDataBaseErr = 34,            //���ݿ�������ӻ��������
	SC_ErrUserNoPrivilege = 32,	  //û��Ȩ��
	SC_ErrNoResources = 30,  //û����Ҫ����Դ
	SC_ErrDataOverflow = 29,
	SC_ErrReceiveDataErr = 27,//�������ݴ���
	SC_ErrTimeOut = 18, //��ʱ
	SC_ErrAlreadyExisted = 20,    //�Ѿ�����
	SC_ErrOpenFileFailed = 6,	//���ļ�ʧ��
	SC_ErrNotConnected = 38,		//û�н�������
	SC_ErrPrivilegeOccupied = 35,  //Ȩ�ޱ�ռ��
	SC_ErrOpen = 39,					//��ʧ��
	SC_ErrRead = 40,					//��ȡʧ��
	SC_ErrNoUsefulData = 41,			//û�п�������

}ScErr;

#define SC_ErrNodeNotExist SC_ErrNotExist


#endif 