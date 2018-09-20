#include "UpdaterWindow.h"

HWND UpdaterWindow::label;
bool UpdaterWindow::updateComplete = false;

MSG UpdaterWindow::CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow)
{
    wc.lpfnWndProc = WindowProc;
    strClassName = "mainWindow";
    windowTitle = "ArcUpdater v" + applicationVersion;
    windowWidth = 400;
    windowHeight = 300;
    windowStartX = (GetSystemMetrics(0) / 2) - (windowWidth / 2);
    windowStartY = (GetSystemMetrics(1) / 2) - (windowHeight / 2);
    
    return GenericWindow::CreateNewWindow(Msg, hInstance, nCmdShow);
}

LRESULT CALLBACK UpdaterWindow::WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
    if(UpdaterWindow::GetStatus())
    {
        message = WM_DESTROY;
    }
    
    switch(message)
    {
        case WM_CLOSE: DestroyWindow(thisWindow); break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(thisWindow, message, wParam, lParam);
    }
    
    return 0;
}

void UpdaterWindow::CreateComponents()
{
    label = CreateChildLabel("Checking for updates...", 115, 75, thisWindow, LBL_UPD);
}

void UpdaterWindow::SetLabel(string newText)
{
    // TODO: Will need to update the position of the label depending on the length of the string
    SetWindowText(label, newText.c_str());
}

void UpdaterWindow::UpdateComplete()
{
    updateComplete = true;
}

bool UpdaterWindow::GetStatus()
{
    return updateComplete;
}