#ifndef PLAYERSPANEL_H
#define PLAYERSPANEL_H

#include <windows.h>
#include <vector>
#include <gdiplus.h>
#include <iostream>

#include "../handler/PlayerHandler.h"

using namespace std;
using namespace Gdiplus;

class PlayersPanel
{
    public:
        static HWND Init(HWND parentWindow, HINSTANCE newInstance, vector<Image*> newImages);
        
        static LRESULT CALLBACK WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam);
        static void WMPaint(HWND thisPanel, HDC hdc, HDC hdcBuffer, PAINTSTRUCT ps);
    private:
        static HWND thisPanel;
        static HINSTANCE instance;
        static RECT background;
        static vector<Image*> images;
        
        static const int panelWidth;
        static const int panelHeight;
};

#endif

