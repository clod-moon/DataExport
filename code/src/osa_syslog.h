#ifndef __OSA_SYSLOG_H_
#define __OSA_SYSLOG_H_


#ifndef WIN32
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/**
*@func 应用程序使用系统syslogd记录日志的模块，为了单个进程的不同日志等级能够单独控制，所以不使用系统的日志控制等级
*/

typedef enum tagLogLevel
{
	SYSLOG_DEBUG = 1,
	SYSLOG_INFO,
	SYSLOG_WARN,
	SYSLOG_ERROR
}ELogLevel;


/**
*日志等级控制文件,只显示比此等级（包含此等级）高的日志,可以调用"echo 日志等级 > /dev/shm/syslog_level.private"来动态
*调整日志的输出，日志等级的取值范围[1,4],参见ELogLevel
*@note 该文件是内存文件，设备重启后会清空
*/
#define SYSLOG_LEVEL_FILE "/dev/shm/syslog_level.private"

/**
*使能日志记录，如果禁用某一级别日志，注掉即可
*/
#define SYSLOG_ENABLE_ERROR
#define SYSLOG_ENABLE_WARN
#define SYSLOG_ENABLE_INFO
#define SYSLOG_ENABLE_DEBUG

#ifdef __cplusplus
	extern "C" {
#endif

/**
*@brief error等级的日志函数
*@param format 同printf的参数
*/
void syslog_error(const char *format, ...);
/**
*@brief ditto
*/
void syslog_warn(const char *format, ...);
/**
*@brief ditto
*/
void syslog_info(const char *format, ...);
/**
*@brief ditto
*/
void syslog_debug(const char *format, ...);
#ifdef __cplusplus
	}
#endif

#endif

#endif
