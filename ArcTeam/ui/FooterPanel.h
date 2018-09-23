#ifndef FOOTERPANEL_H
#define FOOTERPANEL_H

#include <windows.h>
#include <vector>
#include <gdiplus.h>
#include <iostream>

using namespace std;
using namespace Gdiplus;

class FooterPanel
{
    public:
        static HWND Init(HWND parentWindow, HINSTANCE newInstance);
        
        static LRESULT CALLBACK WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam);
        static void WMPaint(HWND thisPanel, HDC hdc, HDC hdcBuffer, HDC hdcMask, HDC hdcMaskTwo, PAINTSTRUCT ps);
        static void WMMouseMove(HWND thisPanel);
        static void WMMouseHover(HWND thisPanel, LPARAM lParam);
        static void WMMouseLeave();
        static void WMTimer(HWND thisPanel);
    private:
        static HWND thisPanel;
        static HINSTANCE instance;
        static vector<Image*> images;
        static int displayImage;
        static int oldDisplayImage;
        static RECT background;
        static RECT dotaRect;
        static RECT heroesRect;
        static RECT positionsRect;
        static RECT modesRect;
        static bool mouseOver;
        
        static const int panelWidth;
        static const int panelHeight;
        static const vector<string> imageNames;
};

#endif

