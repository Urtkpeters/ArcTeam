#ifndef UPDATERWINDOW_H
#define UPDATERWINDOW_H

#include <windows.h>
#include <string>
#include <iostream>

#include "../resources/resources.h"
#include "../handler/ErrorHandler.h"
#include "../handler/DownloadHandler.h"

using namespace std;

class UpdaterWindow
{
    public:
        static MSG CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow);
        static void SetLabel(string newText);
        static void SetLabel(char* resArray);
        static void UpdateComplete();
        static bool GetStatus();
        
        static LRESULT CALLBACK WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam);
        static void WMCommand(WPARAM wParam);
    private:
        static HINSTANCE instance;
        static int cmdShow;
        static WNDCLASSEX wc;
        static HWND thisWindow;
        static HWND label;
        static HWND retryButton;
        static HWND doneButton;
        
        static const string applicationVersion;
        static const int IMG_TITLEBAR;
        static const int LBL_UPD = 100;
        static const int BTN_RTY = 101;
        static const int BTN_DON = 102;
};

#endif

