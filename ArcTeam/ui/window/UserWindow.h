#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <vector>
#include <windows.h>
#include <gdiplus.h>

#include "GenericWindow.h"

using namespace std;
using namespace Gdiplus;

class UserWindow: public GenericWindow 
{
    public:
        MSG CreateNewWindow(MSG Msg, HINSTANCE hInstance, int wCmdShow);
        
        static LRESULT CALLBACK WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT WMCtlColorStatic(WPARAM wParam);
        static void WMPaint(HWND thisWindow);
        static void WMLeftMouseButtonUp(HWND thisWindow, LPARAM lParam);
        static void WMMouseMove(HWND thisWindow);
        static void WMMouseHover(HWND thisWindow, LPARAM lParam);
        static void WMMouseLeave(HWND thisWindow, WPARAM wParam);
        static void WMTimer(HWND thisWindow);
        static LRESULT NCHitTest(HWND thisWindow, LPARAM lParam);
    protected:
        void CreateComponents();
        
        static RECT titleBar;
        static RECT background;
        static RECT closeButton;
        static RECT oneButton;
        static RECT twoButton;
        static RECT threeButton;
        static RECT fourButton;
        static RECT fiveButton;
        static vector<Image*> images;
        static int buttonHover;
        static int currentButtonHover;
        static int playerButtonHover;
        static int currentPlayerHover;
        
        static const vector<string> imageNames;
        static const int userWindowWidth;
        static const int userWindowHeight;
        static const int LBL_USR = 100;
        static const int LBL_ONE = 101;
        static const int LBL_TWO = 102;
        static const int LBL_THREE = 103;
        static const int LBL_FOUR = 104;
        static const int LBL_FIVE = 105;
        static const int LBL_TITLE = 106;
        static const int IDD_OPTIONS_CBO = 112;
};

#endif

