#ifndef STATUSPANEL_H
#define STATUSPANEL_H

#include <windows.h>
#include <vector>
#include <gdiplus.h>
#include <iostream>

#include "../../handler/PlayerHandler.h"
#include "../../handler/UserHandler.h"

using namespace std;
using namespace Gdiplus;

class StatusPanel
{
    public:
        static HWND Init(HWND parentWindow, HINSTANCE newInstance);
        static vector<Image*> GetImages();
        
        static LRESULT CALLBACK WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam);
        static void WMPaint(HWND thisPanel);
        static void WMLeftMouseButtonUp(HWND thisPanel, LPARAM lParam);
        static void WMMouseMove(HWND thisPanel);
        static void WMMouseHover(LPARAM lParam);
        static void WMTimer(HWND thisPanel);
        static void HoverCheck();
    private:
        static HWND thisPanel;
        static HINSTANCE instance;
        static RECT background;
        static RECT happyButton;
        static RECT goodButton;
        static RECT sadButton;
        static RECT fineButton;
        static vector<Image*> images;
        static vector<string> statuses;
        static int selectedButton;
        static int currentSelectedButton;
        static int buttonHover;
        static int currentButtonHover;
        static int mouseTimer;
        static HCURSOR hand;
        static HCURSOR arrow;
        
        static const int panelWidth;
        static const int panelHeight;
        
        static void ChangeState(HWND thisPanel, int state);
};

#endif

