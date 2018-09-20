#include "GenericWindow.h"

const string GenericWindow::applicationVersion = "1.2.0";
const int GenericWindow::IMG_TITLEBAR = ICO_TITLEBAR;

MSG GenericWindow::CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow)
{
    int strLength = strClassName.length();
    char windowClassName[strLength+1];
    strcpy(windowClassName,strClassName.c_str());
    
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
    wc.hIconSm       = LoadIcon(instance, MAKEINTRESOURCE(IMG_TITLEBAR));

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }
    
    return DisplayWindow(Msg);
}

HWND GenericWindow::CreateChildInput(int elementStartX, int elementStartY, int elementWidth, int elementHeight, HWND parentElement, int elementId)
{
    return CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("edit"), NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, elementStartX, elementStartY, elementWidth, elementHeight, parentElement, (HMENU) elementId, NULL, NULL);
}

HWND GenericWindow::CreateChildListbox(int elementStartX, int elementStartY, int elementWidth, int elementHeight, HWND parentElement, int elementId)
{
    return CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, elementStartX, elementStartY, elementWidth, elementHeight, parentElement, (HMENU) elementId, NULL, NULL);
}

HWND GenericWindow::CreateChildLabel(string labelText, int elementStartX, int elementStartY, HWND parentElement, int elementId)
{
    return CreateWindow("static", labelText.c_str(), WS_CHILD | WS_VISIBLE, elementStartX, elementStartY, 100, 25, parentElement, (HMENU)elementId, instance, NULL);
}

void GenericWindow::CreateChildButton(string labelText, int elementStartX, int elementStartY, int elementWidth, int elementHeight, HWND parentElement, int elementId)
{
    CreateWindow("BUTTON", labelText.c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD , elementStartX, elementStartY, elementWidth, elementHeight, parentElement, (HMENU)elementId, (HINSTANCE) 1, NULL);
}

void GenericWindow::CreateChildImageButton(int imageId, int elementStartX, int elementStartY, int elementWidth, int elementHeight, HWND parentElement, int elementId)
{
    HWND imageButton = CreateWindow("BUTTON", "Button Pic", WS_VISIBLE | WS_CHILD | BS_BITMAP , elementStartX, elementStartY, elementWidth, elementHeight, parentElement, (HMENU)elementId, (HINSTANCE) 1, NULL);
    HANDLE buttonImage = LoadImage(instance, MAKEINTRESOURCE(imageId), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    SendMessage(imageButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)buttonImage);
}

string GenericWindow::GetInputField(HWND field)
{
    int fieldLen = GetWindowTextLength(field) + 1;
    char* fieldValue = new char[fieldLen];
    GetWindowText(field, &fieldValue[0], 8192);
    
    string returnVar = string(fieldValue);
    
    return returnVar;
}

MSG GenericWindow::DisplayWindow(MSG Msg)
{
    int strLength = strClassName.length();
    char windowClassName[strLength+1];
    strcpy(windowClassName,strClassName.c_str());
    
    thisWindow = CreateWindowEx(WS_EX_CLIENTEDGE, windowClassName, windowTitle.c_str(), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, windowStartX, windowStartY, windowWidth, windowHeight, NULL, NULL, instance, NULL);
    
    CreateComponents();
    
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