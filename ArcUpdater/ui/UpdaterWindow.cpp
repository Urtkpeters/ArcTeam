#include "UpdaterWindow.h"

HINSTANCE UpdaterWindow::instance;
int UpdaterWindow::cmdShow;
WNDCLASSEX UpdaterWindow::wc;
HWND UpdaterWindow::thisWindow;
HWND UpdaterWindow::label;
const string UpdaterWindow::applicationVersion = "1.0.0";
const int UpdaterWindow::IMG_TITLEBAR = ICO_TITLEBAR;

MSG UpdaterWindow::CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow)
{
    string strClassName = "mainWindow";
    string windowTitle = "ArcUpdater v" + applicationVersion;
    
    int strLength = strClassName.length();
    char windowClassName[strLength+1];
    strcpy(windowClassName, strClassName.c_str());
    
    instance = hInstance;
    cmdShow = nCmdShow;
    
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = instance;
    wc.hIcon         = LoadIcon(instance, MAKEINTRESOURCE(IMG_TITLEBAR));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = windowClassName;
    wc.lpfnWndProc   = WindowProc;
    wc.hIconSm       = LoadIcon(instance, MAKEINTRESOURCE(IMG_TITLEBAR));

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }
    
    thisWindow = CreateWindowEx(WS_EX_CLIENTEDGE, windowClassName, windowTitle.c_str(), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, (GetSystemMetrics(0) / 2) - (400 / 2), (GetSystemMetrics(1) / 2) - (300 / 2), 400, 300, NULL, NULL, instance, NULL);
    
    label = CreateWindow("static", "Checking for updates...", WS_CHILD | WS_VISIBLE | SS_CENTER, 105, 75, 160, 25, thisWindow, (HMENU)LBL_UPD, instance, NULL);
    
    ShowWindow(thisWindow, cmdShow);
    UpdateWindow(thisWindow);
    
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        if(!IsDialogMessage(thisWindow, &Msg))
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
    }
    
    return Msg;
}

LRESULT CALLBACK UpdaterWindow::WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CLOSE: DestroyWindow(thisWindow); break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(thisWindow, message, wParam, lParam);
    }
    
    return 0;
}

void UpdaterWindow::SetLabel(string newText)
{
    SetWindowText(label, newText.c_str());
}

void UpdaterWindow::SetLabel(char* resArray)
{
    SetWindowText(label, resArray);
}

void UpdaterWindow::UpdateComplete()
{
    PostMessage(thisWindow, WM_CLOSE, 0, 0);
}