#include "WebHandler.h"

string WebHandler::getUrl = "https://www.odinary.net/event/arcGetVersion";
string WebHandler::dlUrl = "https://www.odinary.net/ArcTeam/";

size_t WebHandler::curlWriteResponse(void *contents, size_t size, size_t nmemb, string *s)
{
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(bad_alloc &e)
    {
        ErrorHandler::WriteError("Unwritable response.", true);
        
        return 0;
    }

    copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    
    return size*nmemb;
}

json WebHandler::SendRequest(string url)
{
    json jsonResponse;
    CURL* curl;
    
    curl = curl_easy_init();
    
    if(curl)
    {
        long responseCode = 0;
        CURLcode curlResponse;
        string response;
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebHandler::curlWriteResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        curlResponse = curl_easy_perform(curl);
        
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        
        curl_easy_cleanup(curl);
        
        if(responseCode != 200 || curlResponse == CURLE_ABORTED_BY_CALLBACK)
        {
            ErrorHandler::WriteError("Unable to connect to web server to get versions.\r\n" + url, true);
            
            string failResponse = "{\"blnSuccess\":false,\"strMessage\":\"Unable to connect to web server.\"}";
            char failArray[74];
            strcpy(failArray, failResponse.c_str());
            
            jsonResponse = json::parse(failArray);
        }
        else
        {
            char resArray[response.length() + 1];
            strcpy(resArray, response.c_str());
            
            jsonResponse = json::parse(resArray);
        }
    }
    else
    {
        ErrorHandler::WriteError("Unable to connect to the internet to get versions.", true);
            
        string failResponse = "{\"blnSuccess\":false,\"strMessage\":\"Unable to connect to the internet.\"}";
        char failArray[76];
        strcpy(failArray, failResponse.c_str());

        jsonResponse = json::parse(failArray);
    }
    
    return jsonResponse;
}

json WebHandler::GetVersions(string currentVersion)
{
    string url = WebHandler::getUrl + "?currentVersion=" + currentVersion;
    json jsonResponse = SendRequest(url);
    
    if(jsonResponse.at("blnSuccess") != true)
    {
        ErrorHandler::WriteError("Web server response not valid.\r\n" + url, true);
    }
    
    return jsonResponse;
}

void WebHandler::DownloadFile(string File)
{
    CURL *curl;
    CURLcode response;
    FILE *fp;
    string appPath = FileHandler::GetAppPath();

    curl = curl_easy_init();
    
    if(curl)
    {
        long responseCode = 0;
        
        if(File.find("\\") != string::npos)
        {
            vector<string> directories = FileHandler::Split(File, '\\');
            string fullPath = appPath + "download\\";
            
            for(int i = 0; i < directories.size(); i++)
            {
                if(i < directories.size() - 1)
                {
                    fullPath += directories[i] + "\\";
                    CreateDirectory(fullPath.c_str(), NULL);
                }
            }
        }
        
        string downloadPath = FileHandler::GetAppPath() + "download\\" + File;
        
        string url = WebHandler::dlUrl + WebHandler::replace(File, "\\", "/");
        
        fp = fopen(downloadPath.c_str(), "wb");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        response = curl_easy_perform(curl);
        
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        
        curl_easy_cleanup(curl);
        fclose(fp);
        
        if(responseCode != 200 || response == CURLE_ABORTED_BY_CALLBACK)
        {
            ErrorHandler::WriteError("Unable to connect to web server to download file.\r\n" + url, true);
        }
    }
    else
    {
        ErrorHandler::WriteError("Unable to connect to the internet to download file.", true);
    }
}

string WebHandler::replace(string str, const string& from, const string& to)
{
    if(from.empty()) return str;
    
    size_t start_pos = 0;
    
    while((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    
    return str;
}

// I did not write this function and have only replaced some of the variable names.
size_t WebHandler::WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}