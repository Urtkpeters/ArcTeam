// Swap bar selection is bugged and only changing the color of the > symbol red
// Swap bar is flickering a lot
// Display error label
// Make both the main and user title bar name look a little more official
// Swap the main panel out when a selection is made
//      The other pages should just hold placeholder images for now, pick something funny

// Need to make the close button not make the page flicker
// Really need to fix the way the inheritance is being done on the windows. 



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

