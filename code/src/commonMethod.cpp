#include "commonMethod.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h>
using namespace std;



long long getSystemTime()
{
	struct timeb t;

	ftime(&t);

	return 1000*t.time + t.millitm;
}

double getDiffTimeSec(time_t start ,time_t end)
{
	return difftime(end,start);
}

ScErr getSubStr(const string sourStr,string descStr,string&subStr)
{
	string strPicID;
	string subId="\"ID\":\""; 
	int position1,position2;
	position1=sourStr.find(descStr)+descStr.length();
	if(position1 < 0 )
	{
		IVE_Logger_AddLog(LOGLEVEL_WARNING, "main.log", __FUNCTION__, "未获取到 %s",descStr.c_str());
		return SC_ErrNotExist;
	}
	else
	{
		position2=sourStr.find("\"",position1);  
		int len = position2-position1;
		subStr.assign(sourStr,position1,len);
	}
	return SC_ErrSuccess;
}

void readfile(string filePath,char* buf)
{
	char buffer[4096];
	FILE *fp; 
	fp = fopen(filePath.c_str(), "r"); 

	if(fp == NULL) 
	{ 
		exit(0); 
	}
	memset(buffer,0,4096);
	int n=fread(buffer,1,4096,fp);
	while(n>0)
	{
		strncat(buf,buffer,n);
		memset(buffer,0,4096);
		n=fread(buffer,1,4096,fp);
	}
	fclose(fp);
}


void findRoundName(map<string,string>& vMap,string strName,vector<string>& veNameArr)
{
	int i=0;
	char szName[128]={0};
	sprintf(szName,"%s%d",strName.c_str(),++i);
	map<string,string>::iterator itMap;
	itMap=vMap.find(szName);
	while (itMap!= vMap.end())
	{
		veNameArr.push_back(itMap->second);
		memset(szName,0x00,sizeof(szName));
		sprintf(szName,"%s%d",strName.c_str(),++i);
		itMap=vMap.find(szName);
	}
}