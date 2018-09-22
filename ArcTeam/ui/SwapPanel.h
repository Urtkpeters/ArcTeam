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
        static void WMPaint(HWND thisPanel, HDC hdc, HDC hdcBuffer, PAINTSTRUCT ps);
    private:
        static HWND thisPanel;
        static HINSTANCE instance;
        static RECT background;
        
        static const int panelWidth;
        static const int panelHeight;
};

#endif

