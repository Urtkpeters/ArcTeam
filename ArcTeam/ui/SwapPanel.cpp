#include "SwapPanel.h"
#include "MainWindow.h"

HWND SwapPanel::thisPanel;
HINSTANCE SwapPanel::instance;
RECT SwapPanel::background;

const int SwapPanel::panelWidth = 400;
const int SwapPanel::panelHeight = 100;

HWND SwapPanel::Init(HWND parentWindow, HINSTANCE newInstance)
{
    instance = newInstance;
    thisPanel = CreateWindowEx(WS_EX_LEFT, "STATIC", NULL, WS_VISIBLE | WS_CHILD, 100, 425, panelWidth, panelHeight, parentWindow, (HMENU) 106, NULL, NULL);
    SetRect(&background, 0, 0, panelWidth, panelHeight);
    
    return thisPanel;
}

LRESULT CALLBACK SwapPanel::WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static HDC hdcBuffer;
    static PAINTSTRUCT ps;
    
    switch(message)
    {
        case WM_ERASEBKGND: return true;
        case WM_PAINT: WMPaint(thisPanel, hdc, hdcBuffer, ps); return false;
        default: return DefWindowProc(thisPanel, message, wParam, lParam);
    }
    
    return MainWindow::WindowProc(thisPanel, message, wParam, lParam);
}

void SwapPanel::WMPaint(HWND thisPanel, HDC hdc, HDC hdcBuffer, PAINTSTRUCT ps)
{
    hdc = BeginPaint(thisPanel, &ps);
    hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbm = CreateCompatibleBitmap(hdc, panelWidth, panelHeight);
    SelectObject(hdcBuffer, hbm);
    
    HBRUSH brush = CreateSolidBrush(RGB(87, 112, 153));
    
    FillRect(hdcBuffer, &background, brush);
    
    BitBlt(hdc, 0, 0, panelWidth, panelHeight, hdcBuffer, 0, 0, SRCCOPY);
    
    DeleteObject(brush);
    DeleteObject(hbm);
    DeleteDC(hdcBuffer);
    
    EndPaint(thisPanel, &ps);
}