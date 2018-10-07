#include "FileHandler.h"
#include "ErrorHandler.h"

void FileHandler::CheckDownloadDirectory()
{
    string downloadPath = GetAppPath() + "download";
    
    DWORD ftyp = GetFileAttributesA(downloadPath.c_str());
    
    if(ftyp != INVALID_FILE_ATTRIBUTES)
    {
        DeleteDirectory(downloadPath);
    }
    
    CreateDirectory(downloadPath.c_str(), NULL);
}

void FileHandler::UnpackDownload()
{
    string basePath = GetAppPath();
    string downloadPath = basePath + "\\download";
    
    DWORD ftyp = GetFileAttributesA(basePath.c_str());
    DWORD ftyp2 = GetFileAttributesA(downloadPath.c_str());
    
    if(ftyp != INVALID_FILE_ATTRIBUTES && ftyp2 != INVALID_FILE_ATTRIBUTES)
    {
        MoveFiles(basePath, downloadPath);
    }
    else
    {
        ErrorHandler::WriteError("Problem occurred when moving downloaded files.\r\n" + downloadPath, true);
    }
}

string FileHandler::GetCurrentVersion()
{
    return ReadVersionFile().at(0);
}

string FileHandler::GetPreviousVersion()
{
    return ReadVersionFile().at(1);
}

vector<string> FileHandler::ReadVersionFile()
{
    string configFilePath = GetAppPath() + "version";
    
    DWORD settingFileAttributes = GetFileAttributes(configFilePath.c_str());
        
    if(settingFileAttributes == INVALID_FILE_ATTRIBUTES || (settingFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
        ErrorHandler::WriteError("Couldn't read version file.", false);
        
        return {"0.0.0", "0.0.0"};
    }
    
    ifstream ifs(configFilePath.c_str());
    string fileContent((istreambuf_iterator<char>(ifs)),(istreambuf_iterator<char>()));
    
    return FileHandler::Split(fileContent, '|');
}

// I did not write this function and have only replaced some of the variable names.
vector<string> FileHandler::Split(const string& inputString, char delimiter)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(inputString);
   while(getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

string FileHandler::GetAppPath()
{
    char appPath[MAX_PATH];
    GetModuleFileName(NULL, appPath, MAX_PATH);
    char* cutoff = strrchr(appPath,'\\');
    *(cutoff+1)='\0';
    
    return (string) appPath;
}

void FileHandler::DeleteDirectory(string filePath)
{
    WIN32_FIND_DATA info;
    HANDLE fileHandler; 
    char fileFound[256];
    
    sprintf(fileFound, "%s\\*.*", filePath.c_str());
    fileHandler = FindFirstFile(fileFound, &info);
    
    while(FindNextFile(fileHandler, &info))
    {
        if(info.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
        {
            sprintf(fileFound,"%s\\%s", filePath.c_str(), info.cFileName);

            string path = (string) fileFound;

            if(path.find("..") == string::npos)
            {
                DeleteDirectory((string) fileFound);
            }
        }
        else
        {
            sprintf(fileFound,"%s\\%s", filePath.c_str(), info.cFileName);

            DeleteFile(fileFound);
        }
    }

    FindClose(fileHandler);

    RemoveDirectory(filePath.c_str());
}

void FileHandler::MoveFiles(string destinationPath, string sourcePath)
{
    WIN32_FIND_DATA info;
    HANDLE fileHandler; 
    char fileFound[256];
    
    sprintf(fileFound, "%s\\*.*", sourcePath.c_str());
    fileHandler = FindFirstFile(fileFound, &info);
    
    while(FindNextFile(fileHandler, &info))
    {
        sprintf(fileFound,"%s\\%s", sourcePath.c_str(), info.cFileName);
        
        string path = (string) fileFound;
        
        if(path.find("..") == string::npos)
        {
            string finalDestination = destinationPath + "\\" + info.cFileName;
            MoveFileEx(fileFound, finalDestination.c_str(), MOVEFILE_REPLACE_EXISTING);
        }
    }

    FindClose(fileHandler);
}