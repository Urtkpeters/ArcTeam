#include "WindowManager.h"

string WindowManager::window = "userWindow";

MSG WindowManager::CreateUI(MSG Msg, HINSTANCE hInstance, int nCmdShow)
{
    while(window != "close")
    {
        if(window == "userWindow")
        {
            window = "close";
            
            UserWindow userWindow;
            userWindow.CreateNewWindow(Msg, hInstance, nCmdShow);
        }
        else if(window == "mainWindow")
        {
            window = "close";
            
            WebHandler::PushStatus(1, UserHandler::GetUsername());
            
            PlayerHandler::Init();
            
            MainWindow::SetUsernames(PlayerHandler::GetUsernames());
            
            PeriodicHandler::CreateThread();
            
            MainWindow mainWindow;
            mainWindow.CreateNewWindow(Msg, hInstance, nCmdShow);
            
            PeriodicHandler::KillThread();
            
            WebHandler::PushStatus(0, UserHandler::GetUsername());
        }
        else
        {
            window = "close";
        }
    }
}

string WindowManager::GetWindow()
{
    return window;
}

void WindowManager::SetWindow(string newWindow)
{
    window = newWindow;
}