#ifndef HTTPCLIENT_H  
#define HTTPCLIENT_H  

#include <map>
#include <string>
using namespace std;
 
int netGet(string url, string params, int timeout, string&result,map<string,string>&m) ;  
int netPost(string uri, string params, int timeout, string&result, map<string,string>&m) ;  
  
 
#endif