#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include <string>
#include <vector>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>

#include "GenericWindow.h"
#include "../handler/WebHandler.h"
#include "../handler/UserHandler.h"
#include "../handler/PlayerHandler.h"

using namespace std;
using namespace Gdiplus;

class MainWindow: public GenericWindow 
{
    public:
        MSG CreateNewWindow(MSG Msg, HINSTANCE hInstance, int wCmdShow);
        
        static HWND mainWindow;
        static RECT background;
        static int userState;
        static int currentUserState;
        static bool firstLoad;
        static vector<string> currentStatus;
        static vector<Image*> images;
        
        static void SetUsernames(vector<string> newUsernames);
        static void SetPlayerStatus(string changeUsername, string statusName);
        static void ChangeState(int state, HWND thisWindow);
        static void RefreshWindow();
        
        static LRESULT CALLBACK WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam);
        static void WMCommand(HWND thisWindow, WPARAM wParam, LPARAM lParam);
        static void WMLeftMouseButtonUp(HWND thisWindow, WPARAM wParam, LPARAM lParam);
        static void WMPaint(HWND thisWindow, WPARAM wParam, LPARAM lParam);
        
        static const string imagePath;
    protected:
        void CreateComponents();
        
        static vector<string> usernames;
        
        static const int LBL_ONE = 100;
        static const int LBL_TWO = 101;
        static const int LBL_THREE = 102;
        static const int LBL_FOUR = 103;
        static const int BTN_ZERO = 104;
        static const int BTN_ONE = 105;
        static const int BTN_TWO = 106;
        static const int BTN_THREE = 107;
};

#endif

