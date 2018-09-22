#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <windows.h>
#include <commctrl.h>
#include <vector>
#include <objidl.h>
#include <gdiplus.h>

#include "GenericWindow.h"
#include "../handler/UserHandler.h"
#include "../handler/PlayerHandler.h"
#include "PlayersPanel.h"
#include "SwapPanel.h"
#include "FooterPanel.h"

using namespace std;
using namespace Gdiplus;

class MainWindow: public GenericWindow 
{
    public:
        MSG CreateNewWindow(MSG Msg, HINSTANCE hInstance, int wCmdShow);
        
        static HWND mainWindow;
        static RECT background;
        static vector<Image*> images;
        
        static void SetUsernames(vector<string> newUsernames);
        static void SetPlayerStatus(string changeUsername, string statusName);
        static void ChangeState(int state, HWND thisWindow);
        static void RefreshWindow();
        static void DisplayError(string errorMessage);
        
        static LRESULT CALLBACK WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam);
        static void WMLeftMouseButtonUp(HWND thisWindow, WPARAM wParam, LPARAM lParam);
        static void WMPaint(HWND thisWindow, WPARAM wParam, LPARAM lParam);
        static LRESULT WMCtlColorStatic(HWND thisWindow, WPARAM wParam, LPARAM lParam, HDC hdc);
        static LRESULT NCHitTest(HWND thisWindow, WPARAM wParam, LPARAM lParam);
    protected:
        void CreateComponents();
        
        static HWND errorLabel;
        static HWND titleLabel;
        static vector<string> usernames;
        
        static const int LBL_ONE = 100;
        static const int LBL_TWO = 101;
        static const int LBL_THREE = 102;
        static const int LBL_FOUR = 103;
        static const int LBL_ERROR = 104;
        static const int LBL_TITLE = 105;
};

#endif

