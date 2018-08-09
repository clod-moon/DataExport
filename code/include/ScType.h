#ifndef SC_TYPE_H
#define SC_TYPE_H


#include "ScErr.h"
#ifndef NULL
#define NULL 0
#endif

#define SC_MAX_PATH 256

//BOOL���Ͷ���
#define OUT
typedef void* HANDLE ;

#define SC_PI 3.1415926

typedef unsigned int Uint32;
typedef unsigned short Uint16;
typedef unsigned char  Uint8;
//�Զ���BYTE ����

typedef enum tagParameterDirectionEnum
{
	ScadParamUnknown		= 0,
	ScadParamInput		= 1,
	ScadParamOutput		= 2,
	ScadParamInputOutput	= 3,
	ScadParamReturnValue	= 4
}ScParamDirectEnum;




// ����ͼ���ʽ: ͼ��Ϊ�������¸�ʽ
typedef enum tagImageType
{
	IT_RGB = 0,       // c0-rgb rgbrgbrgb����洢��ʽ
	IT_YUV420 = 1,    // c0-y,c1-u,c2-v
	IT_BAYER = 2,     // c0-bayer   
	//IT_RGBFIX = 3,    // c0-rgb rgbrgbrgb����洢��ʽ
	IT_JPEG   = 4,    // c0-jpeg 
	IT_YUV422 = 5,    // c0-y,c1-u,c2-v
	IT_YCbCr_VYUY = 6, //c0-vyuy      
	IT_GRAY = 7,     // c0-y ֻ��y������yuvͼ���Ҷ�ͼ��
	IT_YUV422PSemi = 8,  //c0-y c1-uv   tiĳ�����ӵ������ʽ
	IT_RGBY = 9,      //c0-r,c1-g,c2-b c4-y ͬʱ��rgb�ͻҶȣ�ĳЩ������Ż�ʹ��
	IT_32BIT = 10,      //c0-data �����������ͣ��ṩ����������ͼ������
	IT_YCbCr422 = 11,
	IT_YUV420SP_Y_UV = 12
}ScImageType;

#define IT_YUV_Y  IT_GRAY
#define IT_YUV422_VYUY IT_YCbCr_VYUY

typedef struct _ScImage
{
	int  nSize;         /* sizeof(ScImage) */
	int	 nType;			/* Image types :enum ImageType*/
	int  nChannels;     /* Most of OpenCV functions support 1,2,3 or 4 channels */
	int  nDepth;         /* pixel depth in bits: IPL_DEPTH_8U, IPL_DEPTH_8S, IPL_DEPTH_16S,
						 IPL_DEPTH_32S, IPL_DEPTH_32F and IPL_DEPTH_64F are supported */
	int  nOrigin;        /* 0 - top-left origin,
						 1 - bottom-left origin (Windows bitmaps style) */
	int  nWidth;         /* image width in pixels */
	int  nHeight;        /* image height in pixels */
	int  nImageSize;     /* image data size in bytes
						 (==image->height*image->widthStep
						 in case of interleaved data)*/
	int  nWidthStep;		/* size of aligned image row in bytes */
    
	unsigned char * cImageData[4];
}ScImage;

typedef struct tagScFrameData
{
	ScImage* pImage;
	void*    pUserData;
}ScFrameData;

typedef struct _ScRGB
{
	unsigned char  r;
	unsigned char  g;
	unsigned char  b;
}ScRGB;

typedef struct _ScYUV
{
	unsigned char  y;
	unsigned char  u;
	unsigned char  v;
}ScYUV;




//--------------------------------------------------------------------------- ���ζ���
typedef struct _ScPoint
{
	int x;
	int y;
}ScPoint;

//����
typedef struct _ScRect
{
	int left;
	int top;
	int right;
	int bottom;
}ScRect;

typedef struct _ScPointF
{
	float x;
	float y;
}ScPointF, *PScPointF, ScPoint2D32f;

typedef struct _ScRectF
{
	float left;
	float top;
	float right;
	float bottom;
}ScRectF;

typedef struct _ScPoint3D32f
{
	float x;
	float y;
	float z;
}ScPoint3D32f;

#define SC_MAX_POLYGON_LENGTH 100
#define SC_MAX_COUNTPOINTS 20

typedef struct _ScLineSegmentF
{
	ScPointF point1;
	ScPointF point2;
}ScLineSegmentF;

typedef struct _ScLineF
{
	ScPointF vetexes[SC_MAX_COUNTPOINTS];
	int nCountofPoints;
}ScLineF;

typedef struct _ScPolygonF
{
	ScPointF vetexes[SC_MAX_COUNTPOINTS];
	int nCountofPoints;
}ScPolygonF;

//---------------------------------------------------------------------------

#include "ScTypeEx.h"

#define ScSystemTime2SYSTEMTIME(scTime,stTime)  \
	memcpy(&(stTime),&(scTime),sizeof(ScSystemTime))


typedef struct _ScFrame
{
	ScSystemTime    scTimeStamp;				// ��֡ͼ��Ĳ���ʱ��
	ScImage			*pImage;
	unsigned int   lUserData;					// �û��Զ�������
}ScFrame;


#ifndef SC_EXTERN_C
#ifdef __cplusplus
#define SC_EXTERN_C extern "C"
#else //__cplusplus
#define SC_EXTERN_C
#endif //__cplusplus
#endif //SC_EXTERN_C

// SCAPI�����궨�壬��Ҫ�������ӿ�ӿڿ��Է������ַ�ʽ�����Լ��ĵ�����
// ����ǿ�ҽ��鲻Ҫֱ����SCAPI�����ʹ���ˣ�����Ҫ���Լ���Ԥ������ж���SCAPI_EXPORTS��
// 1.0�汾֮��Ļ����⣬��ʹ�ú�SCFL_API������������ʹ����ͬ��Ҳ��Ҫʹ������ꡣ

#ifndef SCAPI
#define SCAPI(rettype) SC_EXTERN_C SC_EXPORTS rettype SC_CDECL
#endif //SCAPI

#define SAFE_DELETE(i) {if (i) {delete (i); i = NULL;}}
#define SAFE_DELETE_ARRAY(i) {if (i) {delete [](i); i = NULL;}}



#ifdef WIN32
	// Windows
	#ifdef WIN64
		#define ScSocket unsigned long long
	#else
		#define ScSocket unsigned int
	#endif
#else
	// Linux
	#ifdef __x86_64__
		#define ScSocket unsigned long long
	#else
		#define ScSocket unsigned int
	#endif
#endif

#endif

