// Close window button hover swap - sets it the first time but can't detect when the hover is ending because you would have to leave the whole window.
//    Need to detect if you have left just the rect of the close button
// Display error label
// Make the user select look appropriate

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>

#include "ui/window/WindowManager.h"

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

