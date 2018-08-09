#ifndef COMMONOBJEXPORT_H_
#define COMMONOBJEXPORT_H_
#include "ScType.h"
#include "IContainerBase.h"

/************************************************************************/
/* ����ֻ��GetKeyList��Ҫ�ǵ�ReleaseKeyList,�����ڴ治�ù�              */
/************************************************************************/


#ifndef VTAPI
#ifdef WIN32
#define VTAPI extern "C" __declspec(dllexport)
#else
#define VTAPI extern "C"
#define __stdcall
#endif	//WIN32
#endif	//VTAPI

typedef void* HCommonObj;


//////////////////////////////////////////////////////////////////////////
/**����������***/
VTAPI ScErr CreateCommonObj(HCommonObj* pHandle);
/**
 * @brief ����XML����CommonObj
 * @return Sc_ErrSuccess �ɹ�,����ʧ��
 */
VTAPI ScErr CreateCommonObjByXml(HCommonObj* pHandle, char* pXml);
VTAPI ScErr DestroyCommonObj(HCommonObj Handle);
// ����һ��hSrc��hDest
VTAPI ScErr CommomObjCopy(HCommonObj hSrc, HCommonObj hDest);

// ������ת������
// pUseLen:�粻Ϊ�գ����ȡʹ���ڴ�ĳ���,Ϊ��Ҳ��
VTAPI ScErr CommonObjToBinary(HCommonObj hCommObj, char* pBuf, int nBufSize, int* pUseLen);
// �������������������ṹ��
// nSize:{����0:���ڵ���pBuf���ݴ�С������ʱ���ܳ����ó���}
// nSize:{-1:��ȷ��ռ�˶���,�ڲ�������������ȷ��pBufʹ�ó���}
VTAPI ScErr BinaryToCommonObj(HCommonObj hCommObj, const char* pBuf, int nSize);

VTAPI unsigned int GetValueTypeByKey(HCommonObj Handle, const char* szKey);
/**
 * @brief ��ȡ�þ���µ�Key���б�,ָ���ָ�벻Ϊ��˵��������,Ϊ��˵���������һ��
 * @return NULL ��ȡʧ�ܡ���ǰ��key
 * @return ��ҪReleaseKeyList�ͷ�
 */
VTAPI const char** GetKeyList(HCommonObj Handle);
/**
 * @brief �ͷŻ�ȡ��KeyList
 */
VTAPI ScErr ReleaseKeyList(HCommonObj Handle, const char** pKeyList);
/**
 * @brief ����Key��ȡvalue
 * @param Handle CommonObj���
 * @param szKey Key�ؼ���
 * @param pType һ��unsigned int��ָ��,���ظùؼ��ֵ�ֵ������
 * @param pData ���ؾ������ݵ�ָ��
 * @param pLen �������ݵĸ���
 */
VTAPI ScErr GetValueByKey(HCommonObj Handle, const char* szKey, OUT unsigned int* pType, OUT void* pData, OUT unsigned int* pLen);
/**
 * @brief ����Key��ȡvalue,�����ο�GetValueByKey
 */

VTAPI ScErr SetValueByKey(HCommonObj Handle, const char* szKey, unsigned int nType, IN void* pData, unsigned int len);
/**
 * @brief ����һ�Լ�ֵ��,�����ο�GetValueByKey
 **/
VTAPI ScErr AddKeyValue(HCommonObj Handle, const char* szKey, unsigned int nType, IN void* pData, unsigned int len);
/**
 * @brief ɾ��һ�Լ�ֵ��
 **/
VTAPI ScErr DelKey(HCommonObj Handle, const char* szKey);

/**
 * @brief ��ȡת��ΪXML��ʽ�������,����Ҫ�ͷ�
 **/
VTAPI const char* GetConvertXml(HCommonObj Handle);

/**
 * @brief ��ȡת��Ϊjson��ʽ�������,����Ҫ�ͷ�
 **/
VTAPI const char* GetConvertJson(HCommonObj Handle);

#endif

