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
            
            UserHandler::SetState(1);
            PlayerHandler::Init();
            
            PeriodicHandler::CreateThread();
            
            MainWindow mainWindow;
            mainWindow.CreateNewWindow(Msg, hInstance, nCmdShow);
            
            PeriodicHandler::KillThread();
    
            while(PeriodicHandler::GetThreadStatus())
            {
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            
            UserHandler::SetState(0);
            
            this_thread::sleep_for(chrono::milliseconds(2000));
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