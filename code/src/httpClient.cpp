#include "ghttp.h"  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <unistd.h>
#include "httpClient.h"
//#include "ulaneLog.h"
#include "IVE_SDK_Export.h"
#include "CommonObjExport.h"
   
 
int netGet(string url, string params, int timeout, string& result,map<string,string>&m) 
{  
	ghttp_status status;
	char* temresult = NULL;
    ghttp_request *request = NULL;  
    request = ghttp_request_new();  
    
	char szUrl[256];
	memset(szUrl,0x00,sizeof(szUrl));
    strcpy(szUrl,url.c_str());
	
    IVE_Logger_AddLog(LOGLEVEL_INFO, "httpClient.log", __FUNCTION__, "ghttp_set_uri begin");  
	if (ghttp_set_uri(request, szUrl) == -1)  
	{
		IVE_Logger_AddLog(LOGLEVEL_INFO, "httpClient.log", __FUNCTION__, "ghttp_set_uri ERR");
		ghttp_clean(request); 
		return -1;
	}  
    IVE_Logger_AddLog(LOGLEVEL_INFO, "httpClient.log", __FUNCTION__, "ghttp_set_uri end");  
    if (ghttp_set_type(request, ghttp_type_get) == -1)  
	{
		IVE_Logger_AddLog(LOGLEVEL_INFO, "httpClient.log", __FUNCTION__, "ghttp_set_type ERR");
		ghttp_clean(request); 
        return -1;  
	}
	map<string,string>::iterator it = m.begin();
	for(it;it!=m.end();it++)
	{
		ghttp_set_header(request, it->first.c_str(),it->second.c_str());

	}
    char timeout_str[10];  
    sprintf(timeout_str, "%d", timeout);  
    ghttp_set_header(request, http_hdr_Timeout, timeout_str);
	ghttp_set_sync(request, ghttp_sync);	
    ghttp_prepare(request);
    status=ghttp_process(request);
	if (status == ghttp_error)
	{
		IVE_Logger_AddLog(LOGLEVEL_INFO, "httpClient.log", __FUNCTION__, "status ERR = %s", ghttp_get_error(request));
		ghttp_request_destroy(request);
		return -1;			 
	}		
       
    temresult = ghttp_get_body(request);   
	result += temresult;
    ghttp_request_destroy(request);
    return 0;  
}  
  
int netPost(string uri, string params, int timeout, string& result, map<string,string>&m) 
{  
	char* temresult = NULL;
    ghttp_request *request = NULL;  
    ghttp_status status;  
    int len;
	char szUri[256];
	memset(szUri,0x00,sizeof(szUri));
	strcpy(szUri,uri.c_str());
    request = ghttp_request_new();  
   	if (ghttp_set_uri(request, szUri) == -1)  
	{
		IVE_Logger_AddLog(LOGLEVEL_INFO, "httpClient.log", __FUNCTION__, "ghttp_set_uri ERR");
		ghttp_clean(request); 
		return -1;
	}  
       
    if (ghttp_set_type(request, ghttp_type_post) == -1)  
	{
		IVE_Logger_AddLog(LOGLEVEL_INFO, "httpClient.log", __FUNCTION__, "ghttp_set_type ERR");
		ghttp_clean(request); 
        return -1;  
	}
	map<string,string>::iterator it = m.begin();
	for(it;it!=m.end();it++)
	{
		ghttp_set_header(request, it->first.c_str(),it->second.c_str());
	}

	ghttp_set_sync(request, ghttp_sync);  
    char timeout_str[10];  
    sprintf(timeout_str, "%d", timeout);
	ghttp_set_header(request, "Content-Type", "application/json"); 	
    ghttp_set_header(request, http_hdr_Timeout, timeout_str);  
	
	char* szParams = new char[params.length()+1];
	memset(szParams,0x00,params.length()+1);
	memcpy(szParams,params.c_str(),params.length());
    len = strlen(szParams);  
    ghttp_set_body(request, szParams, len); // 
    ghttp_prepare(request); 
    status = ghttp_process(request);
    if (status == ghttp_error)  
    {
		IVE_Logger_AddLog(LOGLEVEL_INFO, "httpClient.log", __FUNCTION__, "status ERR = %s",ghttp_get_error(request));
		delete []szParams;
		return -1;
	}
	temresult = ghttp_get_body(request);
	if(temresult)
	{
		result += temresult;
	}
	delete []szParams;
    ghttp_request_destroy(request); 
    return 0;  
}  