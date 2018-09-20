#include <windows.h>
#include <cstdlib>

#include "ui/UpdaterWindow.h"
#include "handler/DownloadHandler.h"
#include "handler/FileHandler.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG Msg;
    ULONG_PTR token;
    
    DownloadHandler::Init();
    
    UpdaterWindow upWin;
    Msg = upWin.CreateNewWindow(Msg, hInstance, nCmdShow);
    
    // Here down is for the execution of the main application
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    string applicationPath = FileHandler::GetAppPath() + "arcteam.exe";
    
    CreateProcess(applicationPath.c_str(), lpCmdLine, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    return Msg.wParam;
}
