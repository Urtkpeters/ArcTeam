#ifndef SWAPPANEL_H
#define SWAPPANEL_H

#include <windows.h>
#include <vector>
#include <gdiplus.h>
#include <iostream>

using namespace std;
using namespace Gdiplus;

class SwapPanel
{
    public:
        static HWND Init(HWND parentWindow, HINSTANCE newInstance);
        
        static LRESULT CALLBACK WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT WMCtlColorStatic(WPARAM wParam);
        static void WMPaint(HWND thisPanel);
        static void WMLeftMouseButtonUp(LPARAM lParam);
        static void WMMouseMove(HWND thisPanel);
        static void WMMouseHover(LPARAM lParam);
        static void WMTimer(HWND thisPanel);
        static void HoverCheck();
        static int GetSelectedButton();
    private:
        static HWND thisPanel;
        static HINSTANCE instance;
        static RECT background;
        static RECT statusButton;
        static RECT heroesButton;
        static RECT positionsButton;
        static RECT modesButton;
        static int selectedButton;
        static int buttonHover;
        static int currentButtonHover;
        static HWND statusHover;
        static HWND heroesHover;
        static HWND positionsHover;
        static HWND modesHover;
        static int mouseTimer;
        
        static const int panelWidth;
        static const int panelHeight;
        static const int LBL_STS = 100;
        static const int LBL_HER = 101;
        static const int LBL_POS = 102;
        static const int LBL_MOD = 103;
        static const int LBL_HST = 104;
        static const int LBL_HHR = 105;
        static const int LBL_HPS = 106;
        static const int LBL_HMD = 107;
};

#endif

