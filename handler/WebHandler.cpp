#include "WebHandler.h"

string WebHandler::pushUrl = "http://www.odinary.net/event/arcAppPush?username={{username}}&status={{status}}";
string WebHandler::getUrl = "http://www.odinary.net/event/arcAppGet";

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
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebHandler::curlWriteResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        curlResponse = curl_easy_perform(curl);
        
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        
        curl_easy_cleanup(curl);
        
        if(responseCode != 200 || curlResponse == CURLE_ABORTED_BY_CALLBACK)
        {
            MainWindow::DisplayError("Unable to connect to web server.");
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
        MainWindow::DisplayError("Unable to connect to the internet.");
    }
    
    return jsonResponse;
}

json WebHandler::PushStatus(int status, string username)
{
    string url = WebHandler::replace(WebHandler::replace(WebHandler::pushUrl, "{{username}}", username), "{{status}}", to_string(status));
    
    json jsonResponse = SendRequest(url);
    
    if(jsonResponse.at("blnSuccess") != true)
    {
        MainWindow::DisplayError("Web server response not valid.");
    }
    
    return jsonResponse;
}

json WebHandler::GetStatus()
{
    json jsonResponse = SendRequest(WebHandler::getUrl);
    
    if(jsonResponse.at("blnSuccess") != true)
    {
        // Throw error
    }
    
    return jsonResponse;
}

string WebHandler::replace(string str, string find, string replace)
{
    size_t startPos = str.find(find);
    
    if(startPos == string::npos)
    {
        return str;
    }
    
    return str.replace(startPos, find.length(), replace);
}