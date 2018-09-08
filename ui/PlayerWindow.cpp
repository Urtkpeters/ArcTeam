#include "PlayerWindow.h"

PlayerWindow::PlayerWindow(HWND newMainWindow, HINSTANCE newInstance, string newUsername, int labelId, int startX, int startY)
{
    username = newUsername;
    mainWindow = newMainWindow;
    instance = newInstance;
    status = "offline";
    
    label = CreateWindow("static", username.c_str(), WS_CHILD | WS_VISIBLE, startX, startY, 100, 25, mainWindow, (HMENU)labelId, instance, NULL);
}

string PlayerWindow::GetUsername()
{
    return username;
}

string PlayerWindow::GetStatus()
{
    return status;
}

void PlayerWindow::SetStatus(string newStatus)
{
    status = newStatus;
    
    RedrawWindow(mainWindow, NULL, NULL, RDW_INVALIDATE);
}