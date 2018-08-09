
#ifndef _DEVINITMETHOD_H_
#define _DEVINITMETHOD_H_

#include <iostream>
#include <string>
#include <map>
using namespace std;

int DevLogin(map<string,string>&m);

int DevRegister(map<string,string>&m,string& errmsg);

int DevGetConfigUrl(map<string,string>&m,string& errmsg);

int DevGetDataAccpetUrl(map<string,string>&m,string& errmsg);

string GetStr(string&uri, string&str);

#endif
