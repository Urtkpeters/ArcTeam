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
#include "../panel/HeroesPanel.h"
#include "../panel/PositionsPanel.h"
#include "../panel/ModesPanel.h"

using namespace std;
using namespace Gdiplus;

class MainWindow: public GenericWindow 
{
    public:
        MSG CreateNewWindow(MSG Msg, HINSTANCE hInstance, int wCmdShow);
        
        static HWND mainWindow;
        
        static void DisplayError();
        
        static LRESULT CALLBACK WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT WMCtlColorStatic(WPARAM wParam);
        static void WMPaint(HWND thisWindow);
        static void WMLeftMouseButtonUp(HWND thisWindow, LPARAM lParam);
        static void WMMouseMove(HWND thisWindow);
        static void WMMouseHover(HWND thisWindow, LPARAM lParam);
        static void WMTimer(HWND thisWindow);
        static LRESULT NCHitTest(HWND thisWindow, LPARAM lParam);
        static void HoverCheck();
    protected:
        void CreateComponents();
        
        static HWND errorLabel;
        static RECT background;
        static vector<Image*> images;
        static RECT closeButton;
        static RECT minimizeButton;
        static RECT errorButton;
        static RECT grabBar;
        static int buttonHover;
        static int currentButtonHover;
        static int mouseTimer;
        static bool displayError;
        
        static const vector<string> imageNames;
        static const int mainWindowWidth;
        static const int mainWindowHeight;
        static const int LBL_ERROR = 100;
        static const int LBL_TITLE = 101;
};

#endif

