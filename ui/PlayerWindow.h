#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <string>
#include <windows.h>

using namespace std;

class PlayerWindow
{
    public:
        PlayerWindow(HWND newMainWindow, HINSTANCE newInstance, string newUsername, int labelId, int startX, int startY);
        string GetUsername();
        string GetStatus();
        void SetStatus(string newStatus);
    private:
        string username;
        string status;
        HWND label;
        HWND mainWindow;
        HINSTANCE instance;
};

#endif

