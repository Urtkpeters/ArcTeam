#ifndef WEBHANDLER_H
#define WEBHANDLER_H

#include <nlohmann/json.hpp>
#include <string>
#include <curl/curl.h>

#include "../ui/MainWindow.h"

using namespace std;
using json = nlohmann::json;

class WebHandler
{
    public: 
        static json PushStatus(int status, string username);
        static json GetStatus();
    private:
        static string pushUrl;
        static string getUrl;
        
        static json SendRequest(string url);
        static size_t curlWriteResponse(void *contents, size_t size, size_t nmemb, string *s);
        static string replace(string str, string find, string replace);
};

#endif