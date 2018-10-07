#include "ErrorHandler.h"

string ErrorHandler::path;
bool ErrorHandler::encErr = false;;

void ErrorHandler::Init(HINSTANCE instance)
{
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(instance, szPath, MAX_PATH);

    path = string(szPath);
    path = path.substr(0, path.length() - 14) + "errorLog.txt";
}

void ErrorHandler::WriteError(string errorMessage, bool fatalError)
{
    if(!encErr)
    {
        encErr = fatalError;
    }
    
    string errorLine = errorMessage + "\r\n";
    
    ofstream outputFile;
    outputFile.open(path.c_str(), ios_base::app);
    outputFile << errorLine.c_str();
    outputFile.close();
}

bool ErrorHandler::CheckErrors() { return encErr; }

void ErrorHandler::ClearErrors() { encErr = false; }