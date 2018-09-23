#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <windows.h>

#include "GenericWindow.h"

class UserWindow: public GenericWindow 
{
    public:
        MSG CreateNewWindow(MSG Msg, HINSTANCE hInstance, int wCmdShow);
        
        static void WMCommand(HWND thisWindow, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam);
    protected:
        void CreateComponents();
        
        static HWND label;
        static bool isRed;
        
        static const int LBL_USR = 109;
        static const int BTN_USR = 110;
        static const int BTN_DPD = 111;
        static const int IDD_OPTIONS_CBO = 112;
};

#endif

