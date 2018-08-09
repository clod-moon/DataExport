#include <stdlib.h>
#include <stdio.h>	
#include <string.h>
#include "DevInitMethod.h"
#include "json/json.h"
#include "httpClient.h"
#include "IVE_SDK_Export.h"
#include "CommonObjExport.h"
using namespace std;

int DevLogin(map<string,string>&m)
{
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "DevLogin begin");
	string uri = m["devLoginPath"];

	map<string,string> header;
	
	Json::Value root;

	root["user_type"] = m["user_type"];
	root["dev_refid"] = m["dev_refid"];
	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "设置包体成功");

	string requestBody = root.toStyledString();
	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "requestBody = %s",requestBody.c_str());	

	string result ="";
	int timeout = atoi(m["timeout"].c_str());
	int ret = netPost(uri,requestBody,timeout,result,header);
	if (ret != 0)
	{
		IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "DevLogin netPost failed");	
		return ret;
	}
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "result = %s",result.c_str());	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "DevLogin sucess");	

	Json::Reader reader;
	Json::Value value;

	if (reader.parse(result, value))
	{
		m["user_unid"] = value["user_unid"].asString(); 
		m["user_type"] = value["user_type"].asString();
		m["atoken"] = value["atoken"].asString();
		m["atoken_edt"] = value["atoken_edt"].asString();
		m["rtoken"] = value["rtoken"].asString();
		m["rtoken_edt"] = value["rtoken_edt"].asString();
	}
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "DevLogin 解包完成");	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "user_unid = %s",m["user_unid"].c_str());
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "user_type = %s",m["user_type"].c_str());	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "atoken = %s",m["atoken"].c_str());
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "atoken_edt = %s",m["atoken_edt"].c_str());	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "rtoken = %s",m["rtoken"].c_str());
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "rtoken_edt = %s",m["rtoken_edt"].c_str());	
	
	return 0;
}

int DevRegister(map<string,string>&m, string& errmsg)
{
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "DevRegister begin");	
	errmsg.clear();
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "DevRegisterPath=%s",m["DevRegisterPath"].c_str());	
	string uri = m["devRegisterPath"].c_str();
	uri += m["user_unid"].c_str();
	
	uri =uri+"/register";
	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "uri = %s",uri.c_str());	
	
	Json::Value root;

	root["dev_refid"] = m["dev_refid"].c_str();
	root["dev_type"] = m["dev_type"].c_str();
	root["dev_name"] = m["dev_name"].c_str();

	string requestBody = root.toStyledString();
	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "requestBody = %s",requestBody.c_str());

	map<string,string> header;

	header["authorization"] = m["atoken"];
	
	string result;
	int timeout = atoi(m["timeout"].c_str());
	int ret = netPost(uri,requestBody,timeout,result,header);

	if (ret!=0)
	{
		IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "DevRegister netPost failed");
		return ret;
	}
	
	Json::Reader reader;
	Json::Value value;

	if (reader.parse(result, value))
	{
		int ecode = value["ecode"].asInt();
		string enote = value["enote"].asString();
		IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "ecode = %d",ecode);
		if(ecode)
		{
			errmsg += enote;
			return -1;
		}
	}
	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "result = %s",result.c_str());
	return 0;
}

int DevGetConfigUrl(map<string,string>&m,string& errmsg)
{
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "DevGetConfigUrl begin");
	string uri = m["getWsUrlPath"].c_str();
	uri += m["user_unid"].c_str();
	uri += "/ws_url?type=devconf_fx";

	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "uri=%s",uri.c_str());
	
	map<string,string> header;
	
	header["authorization"] = m["atoken"];
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "atoken = %s",m["atoken"].c_str());
	string result;
	int timeout = atoi(m["timeout"].c_str());
	int ret = netGet(uri,"",timeout,result,header);

	if (ret!=0)
	{
		IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "ret = %d","get DevGetConfigUrl failed");
		return ret;
	}
	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "result = %s",result.c_str());

	Json::Value root;
	Json::Reader reader;
	string connect_unid;

	if (reader.parse(result,root))
	{
		m["ws_url"] = root["ws_url"].asString();
		if(m["ws_url"].empty())
		{
			IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__, "获取 ws_url 失败");
			return -1;
		}
	}
	
	m["connect_unid"]= GetStr(m["ws_url"],connect_unid);
	return 0;
}


int DevGetDataAccpetUrl(map<string,string>&m, string& errmsg)
{
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__,"DevGetDataAccpetUrl begin");
	
	map<string,string> header;

	header["authorization"] = m["atoken"];
	
	string result;
	int timeout = atoi(m["timeout"].c_str());
	
	string uri = m["getHttpUrlPath"];
	
	IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__,"uri = %s",uri.c_str());
	
	int ret = netGet(uri,"",timeout,result,header);
	
	if (ret!=0)
	{
		IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__,"DevGetDataAccpetUrl netGet failed");
		return ret;
	}
	
	Json::Value root;
	Json::Reader reader;
	
	if (reader.parse(result,root))
	{
		m["http_url"] = root["http_url"].asString();
		if(m["http_url"].empty())
		{
			IVE_Logger_AddLog(LOGLEVEL_INFO, "DevInitMethod.log", __FUNCTION__,"enote = %s",root["enote"].asString().c_str());
			return -1;
		}
	}
	
	return 0;
}

string GetStr(string&uri, string&str)
{
	int pos = uri.rfind("/")+1;
	
	string temstr(uri,pos);
	
	str += temstr;
	
	return str;
}
