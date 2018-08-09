#ifndef COMMONOBJEXPORT_H_
#define COMMONOBJEXPORT_H_
#include "ScType.h"
#include "IContainerBase.h"

/************************************************************************/
/* 其中只有GetKeyList需要记得ReleaseKeyList,其他内存不用管              */
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
/**创建、销毁***/
VTAPI ScErr CreateCommonObj(HCommonObj* pHandle);
/**
 * @brief 根据XML创建CommonObj
 * @return Sc_ErrSuccess 成功,其他失败
 */
VTAPI ScErr CreateCommonObjByXml(HCommonObj* pHandle, char* pXml);
VTAPI ScErr DestroyCommonObj(HCommonObj Handle);
// 复制一份hSrc到hDest
VTAPI ScErr CommomObjCopy(HCommonObj hSrc, HCommonObj hDest);

// 自描述转二进制
// pUseLen:如不为空，则获取使用内存的长度,为空也可
VTAPI ScErr CommonObjToBinary(HCommonObj hCommObj, char* pBuf, int nBufSize, int* pUseLen);
// 根据数据重设自描述结构体
// nSize:{大于0:大于等于pBuf数据大小，解析时不能超过该长度}
// nSize:{-1:不确定占了多少,内部根据内容自行确定pBuf使用长度}
VTAPI ScErr BinaryToCommonObj(HCommonObj hCommObj, const char* pBuf, int nSize);

VTAPI unsigned int GetValueTypeByKey(HCommonObj Handle, const char* szKey);
/**
 * @brief 获取该句柄下的Key的列表,指针的指针不为空说明有数据,为空说明到了最后一条
 * @return NULL 获取失败、或当前无key
 * @return 需要ReleaseKeyList释放
 */
VTAPI const char** GetKeyList(HCommonObj Handle);
/**
 * @brief 释放获取的KeyList
 */
VTAPI ScErr ReleaseKeyList(HCommonObj Handle, const char** pKeyList);
/**
 * @brief 根据Key获取value
 * @param Handle CommonObj句柄
 * @param szKey Key关键字
 * @param pType 一个unsigned int类指针,返回该关键字的值的类型
 * @param pData 返回具体数据的指针
 * @param pLen 返回数据的个数
 */
VTAPI ScErr GetValueByKey(HCommonObj Handle, const char* szKey, OUT unsigned int* pType, OUT void* pData, OUT unsigned int* pLen);
/**
 * @brief 根据Key获取value,参数参考GetValueByKey
 */

VTAPI ScErr SetValueByKey(HCommonObj Handle, const char* szKey, unsigned int nType, IN void* pData, unsigned int len);
/**
 * @brief 增加一对键值对,参数参考GetValueByKey
 **/
VTAPI ScErr AddKeyValue(HCommonObj Handle, const char* szKey, unsigned int nType, IN void* pData, unsigned int len);
/**
 * @brief 删除一对键值对
 **/
VTAPI ScErr DelKey(HCommonObj Handle, const char* szKey);

/**
 * @brief 获取转换为XML格式后的数据,不需要释放
 **/
VTAPI const char* GetConvertXml(HCommonObj Handle);

/**
 * @brief 获取转换为json格式后的数据,不需要释放
 **/
VTAPI const char* GetConvertJson(HCommonObj Handle);

#endif

