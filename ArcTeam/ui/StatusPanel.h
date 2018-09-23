#ifndef STATUSPANEL_H
#define STATUSPANEL_H

#include <windows.h>
#include <vector>
#include <gdiplus.h>
#include <iostream>

#include "../handler/PlayerHandler.h"
#include "../handler/UserHandler.h"

using namespace std;
using namespace Gdiplus;

class StatusPanel
{
    public:
        static HWND Init(HWND parentWindow, HINSTANCE newInstance);
        static vector<Image*> GetImages();
        
        static LRESULT CALLBACK WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam);
        static void WMLeftMouseButtonUp(HWND thisPanel, WPARAM wParam, LPARAM lParam);
        static void WMPaint(HWND thisPanel, HDC hdc, HDC hdcBuffer, PAINTSTRUCT ps);
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
        
        static const int panelWidth;
        static const int panelHeight;
        
        static void ChangeState(int state);
};

#endif

