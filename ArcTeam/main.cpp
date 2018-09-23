// Check to see if the "Refresh Window" can be sent to the Panel instead, which will help the redraw speed alot
// Fix the flickering. Probably through adding a "title bar"
// Check to see if panels can be merged into a generic
// Reorganize the UI files into two directories. Windows and Panels.
// Username orientation

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>

#include "ui/WindowManager.h"

using namespace std;
using namespace Gdiplus;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG Msg;
    ULONG_PTR token;
    GdiplusStartupInput input;
    GdiplusStartup(&token, &input, NULL);
    ErrorHandler::Init(hInstance);
    
    Msg = WindowManager::CreateUI(Msg, hInstance, nCmdShow);
    
    GdiplusShutdown(token);
    
    return Msg.wParam;
}

