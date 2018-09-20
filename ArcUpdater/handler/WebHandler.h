#ifndef WEBHANDLER_H
#define WEBHANDLER_H

#include <nlohmann/json.hpp>
#include <string>
#include <curl/curl.h>

#include "ErrorHandler.h"
#include "FileHandler.h"

using namespace std;
using json = nlohmann::json;

class WebHandler
{
    public: 
        static json GetVersions(string currentVersion);
        static void DownloadFile(string file);
    private:
        static string getUrl;
        static string dlUrl;
        
        static json SendRequest(string url);
        static size_t curlWriteResponse(void *contents, size_t size, size_t nmemb, string *s);
        static string replace(string str, const string& from, const string& to);
        static size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream);
};

#endif