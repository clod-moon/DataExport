#ifndef _COMMON_METHOD__H_
#define _COMMON_METHOD__H_
#include "ScErr.h"
#include <stdio.h>
#include <string>
#include <list>
#include <map>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include "IVE_SDK_Export.h"
using namespace std;


struct dataImportInfo;
struct msgInfo;

typedef ScErr (* callBackFunc)(dataImportInfo&);

struct msgInfo
{
	string		strMsg;
	time_t		msgStart;
};

struct dataImportInfo{
	string			strIp;
	int				nPort;
	__ConnHndl		*pHandle;
	HCommonObj		hObj;
	list<string>	msgIdlist;
	callBackFunc    mFunc;
};

double getDiffTimeSec(time_t start ,time_t end);

long long getSystemTime();

void readfile(string filePath,char* buf);

void findRoundName(map<string,string>& vMap,string strName,vector<string>& veNameArr);

ScErr getSubStr(const string sourStr,string descStr,string&subStr);
//void RecvAnalyseRet(inArgs&inargs);

void* working(void *arg);

void* MonitorAtoken(void* arg);

void* scalerNum(void* arg);

void* autoReconnect(void* args);

void* testPthead(void* args);

void* sendToDataImport(void* args);

ScErr resendMsgTOJava(string& strMsg,int num);


#endif //IVE_SERVER_TEST_H