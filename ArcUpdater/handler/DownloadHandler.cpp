#include "DownloadHandler.h"

void DownloadHandler::Init()
{
    thread downloadThread(CheckVersion);
    downloadThread.detach();
}

void DownloadHandler::CheckVersion()
{
    string currentVersion = FileHandler::GetCurrentVersion();
    json versionJSON = WebHandler::GetVersions(currentVersion);
    
    vector<string> files;
    bool hasVersions = false;
    bool pushFile;
    int counter = 0;
    
    while(!hasVersions)
    {
        try
        {
            json versionObj = versionJSON.at(to_string(counter));
            
            vector<string> tempFiles = FileHandler::Split(versionObj.at("files"), '|');
            
            for(int i = 0; i < tempFiles.size(); i++)
            {
                pushFile = true;
                
                for(int j = 0; j < files.size(); j++)
                {
                    if(tempFiles[i] == files[j])
                    {
                        pushFile = false;
                        break;
                    }
                }
                
                if(pushFile)
                {
                    files.push_back(tempFiles[i]);
                    pushFile = false;
                }
            }
            
            counter++;
        }
        catch(json::exception &e)
        {
            if(e.id == 403)
            {
                break;
            }
            else
            {
                // Throw error
            }
        }
    }
    
    UpdaterWindow::SetLabel("Checking files...");
    FileHandler::CheckDownloadDirectory();
    
    UpdaterWindow::SetLabel("Downloading...");
    
    // Version is split into three segments x.x.x and this compares each segment one at a time for the current version and the version reported on the site
    for(int i = 0; i < files.size(); i++)
    {
        WebHandler::DownloadFile(files[i]);
    }
    
    UpdaterWindow::SetLabel("Unpacking...");
    FileHandler::UnpackDownload();
    
    UpdaterWindow::UpdateComplete();
}