#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <windows.h>
#include <commctrl.h>
#include <vector>
#include <objidl.h>
#include <gdiplus.h>

#include "GenericWindow.h"
#include "../../handler/UserHandler.h"
#include "../panel/PlayersPanel.h"
#include "../panel/SwapPanel.h"

using namespace std;
using namespace Gdiplus;

class MainWindow: public GenericWindow 
{
    public:
        MSG CreateNewWindow(MSG Msg, HINSTANCE hInstance, int wCmdShow);
        
        static HWND mainWindow;
        static RECT background;
        
        static void SetUsernames(vector<string> newUsernames);
        static void SetPlayerStatus(string changeUsername, string statusName);
        static void RefreshWindow();
        static void DisplayError(string errorMessage);
        
        static LRESULT CALLBACK WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT WMCtlColorStatic(WPARAM wParam);
        static void WMPaint(HWND thisWindow);
        static void WMLeftMouseButtonUp(HWND thisPanel, LPARAM lParam);
        static LRESULT NCHitTest(HWND thisWindow, LPARAM lParam);
    protected:
        void CreateComponents();
        
        static HWND errorLabel;
        static HWND titleLabel;
        static vector<string> usernames;
        static vector<Image*> images;
        
        static const vector<string> imageNames;
        static const int mainWindowWidth;
        static const int mainWindowHeight;
        static const int LBL_ERROR = 100;
        static const int LBL_TITLE = 101;
};

#endif

