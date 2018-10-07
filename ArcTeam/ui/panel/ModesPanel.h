#ifndef MODESPANEL_H
#define MODESPANEL_H

#include <windows.h>
#include <vector>
#include <gdiplus.h>
#include <iostream>

using namespace std;
using namespace Gdiplus;

class ModesPanel
{
    public:
        static HWND Init(HWND parentWindow, HINSTANCE newInstance);
        static void RefreshPanel();
        static void HidePanel();
        static void ShowPanel();
        
        static LRESULT CALLBACK WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT WMCtlColorStatic(WPARAM wParam);
        static void WMPaint(HWND thisPanel);
    private:
        static HWND thisPanel;
        static HINSTANCE instance;
        static RECT background;
        static vector<Image*> images;
        
        static const vector<string> heroes;
        static const int panelWidth;
        static const int panelHeight;
        static const int PNL_ONE = 100;
};

#endif

