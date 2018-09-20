#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H

#include <iostream>

#include "GenericWindow.h"

using namespace std;

class UpdaterWindow: public GenericWindow 
{
    public:
        MSG CreateNewWindow(MSG Msg, HINSTANCE hInstance, int wCmdShow);
        
        static void SetLabel(string newText);
        static void UpdateComplete();
        static bool GetStatus();
        
        static LRESULT CALLBACK WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam);
    protected:
        void CreateComponents();
    private:
        static HWND label;
        static bool updateComplete;
        
        static const int LBL_UPD = 100;
};

#endif

