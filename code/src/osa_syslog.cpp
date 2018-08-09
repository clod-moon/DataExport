#include "osa_syslog.h"

#define    QUICK_LOG(level,prefix)   do {			\
		int dynamicLogLevel = get_daynamic_log_level(); \
        	if(level >= dynamicLogLevel)			\
        	{						\
			int len = strlen(format) + 128;		\
			char *newFormat = (char*)malloc(len);	\
			assert(newFormat != NULL);		\
                	va_list ap;				\
                	va_start(ap,format);			\
			sprintf(newFormat,"%s %s",prefix,format);\
                	vsyslog(LOG_ERR,newFormat,ap);		\
                	va_end(ap);				\
			free(newFormat);			\
			newFormat = NULL;			\
        	}						\
	}while(0)						




int get_daynamic_log_level()
{
        int dynamicLogLevel = 0;
        //动态读取日志级别
        FILE *pf = fopen(SYSLOG_LEVEL_FILE,"r");
        if(NULL == pf)
        {
                dynamicLogLevel = (int)SYSLOG_INFO;
        }
        else
        {
                char buf[8] = "\0";
		if(NULL != fgets(buf,sizeof(buf),pf))
		{
			dynamicLogLevel = atoi(buf);
		} 
                fclose(pf);
        }
	return dynamicLogLevel;
}


/**
*@brief error等级的日志函数
*@param format 同printf的参数
*/
void syslog_error(const char *format, ...)
{
#ifdef SYSLOG_ENABLE_ERROR
	QUICK_LOG(SYSLOG_ERROR,"[ERROR]");
#endif
}
/**
*@brief ditto
*/
void syslog_warn(const char *format, ...)
{
#ifdef SYSLOG_ENABLE_WARN
	QUICK_LOG(SYSLOG_WARN,"[WARN]");
#endif
}
/**
*@brief ditto
*/
void syslog_info(const char *format, ...)
{
#ifdef SYSLOG_ENABLE_INFO
	QUICK_LOG(SYSLOG_INFO,"[INFO]");
#endif
}
/**
*@brief ditto
*/
void syslog_debug(const char *format, ...)
{
#ifdef SYSLOG_ENABLE_DEBUG
	QUICK_LOG(SYSLOG_DEBUG,"[DEBUG]");
#endif
}
