#ifndef SC_TYPE_LINUX_H
#define SC_TYPE_LINUX_H

#ifndef OUT
#define OUT
#endif
#ifndef IN
#define IN
#endif
#ifndef BOOL
#define BOOL int
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef WCHAR
#define WCHAR wchar_t
#endif

#ifndef WORD
#define WORD unsigned short
#endif
#ifndef DWORD
#define DWORD unsigned long
#endif
#ifndef SOCKET
#define SOCKET unsigned int
#endif
#ifndef MYSOCKET
#define MYSOCKET unsigned int
#endif
#ifndef BYTE
#define BYTE unsigned char
#endif
#ifndef UINT
#define UINT unsigned int
#endif
#ifndef PBYTE
#define PBYTE unsigned char *
#endif
#ifndef UINT_PTR
#define UINT_PTR unsigned int
#endif
#ifndef CALLBACK
#define CALLBACK
#endif
#ifndef MAX_PATH
#define MAX_PATH 512
#endif

#ifndef __stdcall
#define __stdcall
#endif

typedef struct _ScSystemTime
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
}ScSystemTime;

#ifndef RECT
	//defined in windef.h
	typedef struct tagRECT
	{
    	int    left;
    	int    top;
    	int    right;
    	int    bottom;
	} RECT;
#endif

#define SC_EXPORTS __attribute ((visibility("default")))
#ifndef WCHAR
#define WCHAR unsigned short
#endif

#ifndef restrict
#define restrict
#endif

#ifdef UNICODE
#define TCHAR wchar_t
#define _T L
#else
#define TCHAR char
#define _T
#endif

#define LPCTSTR const TCHAR *
#define LPTSTR TCHAR *
#define LPCSTR const char*

#define SC_CDECL
#define SC_STDCALL
//#define SC_EXPORTS

#define SC_DLLEXPORT
#define SC_DLLIMPORT

#define INVALID_SOCKET -1
#endif

