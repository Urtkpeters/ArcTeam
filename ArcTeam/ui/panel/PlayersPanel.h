#ifndef PLAYERSPANEL_H
#define PLAYERSPANEL_H

#include <windows.h>
#include <vector>
#include <gdiplus.h>
#include <iostream>

#include "../../handler/PlayerHandler.h"
#include "StatusPanel.h"

using namespace std;
using namespace Gdiplus;

class PlayersPanel
{
    public:
        static HWND Init(HWND parentWindow, HINSTANCE newInstance);
        
        static LRESULT CALLBACK WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT WMCtlColorStatic(WPARAM wParam);
        static void WMPaint(HWND thisPanel);
        static void RefreshPanel();
    private:
        static HWND thisPanel;
        static HINSTANCE instance;
        static RECT background;
        static vector<Image*> images;
        static vector<string> statuses;
        
        static const int panelWidth;
        static const int panelHeight;
        static const int PNL_ONE = 100;
        static const int LBL_ONE = 101;
        static const int LBL_TWO = 102;
        static const int LBL_THREE = 103;
        static const int LBL_FOUR = 104;
};

#endif

