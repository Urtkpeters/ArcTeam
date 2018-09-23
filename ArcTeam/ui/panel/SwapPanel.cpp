#include "SwapPanel.h"
#include "../window/MainWindow.h"

HWND SwapPanel::thisPanel;
HINSTANCE SwapPanel::instance;
RECT SwapPanel::background;
RECT SwapPanel::statusButton;
RECT SwapPanel::heroesButton;
RECT SwapPanel::positionsButton;
RECT SwapPanel::modesButton;
int SwapPanel::selectedButton;
int SwapPanel::buttonHover;
int SwapPanel::currentButtonHover;
bool SwapPanel::mouseOver;
HWND SwapPanel::statusHover;
HWND SwapPanel::heroesHover;
HWND SwapPanel::positionsHover;
HWND SwapPanel::modesHover;

const int SwapPanel::panelWidth = 100;
const int SwapPanel::panelHeight = 550;

HWND SwapPanel::Init(HWND parentWindow, HINSTANCE newInstance)
{
    instance = newInstance;
    thisPanel = CreateWindowEx(WS_EX_LEFT, "STATIC", NULL, WS_VISIBLE | WS_CHILD, 0, 20, panelWidth, panelHeight, parentWindow, (HMENU) 106, NULL, NULL);
    selectedButton = 0;
    buttonHover = 0;
    
    SetRect(&background, 0, 0, panelWidth, panelHeight);
    SetRect(&statusButton, 0, 0, panelWidth, 50);
    SetRect(&heroesButton, 0, 50, panelWidth, 100);
    SetRect(&positionsButton, 0, 100, panelWidth, 150);
    SetRect(&modesButton, 0, 150, panelWidth, 200);
    
    CreateWindow("static", "Status", WS_CHILD | WS_VISIBLE, 5, 15, 100, 25, thisPanel, (HMENU)LBL_STS, instance, NULL);
    CreateWindow("static", "Heroes", WS_CHILD | WS_VISIBLE, 5, 65, 100, 25, thisPanel, (HMENU)LBL_HER, instance, NULL);
    CreateWindow("static", "Positions", WS_CHILD | WS_VISIBLE, 5, 115, 100, 25, thisPanel, (HMENU)LBL_POS, instance, NULL);
    CreateWindow("static", "Modes", WS_CHILD | WS_VISIBLE, 5, 165, 100, 25, thisPanel, (HMENU)LBL_MOD, instance, NULL);
    
    statusHover = CreateWindow("static", ">", WS_CHILD | WS_VISIBLE, 80, 15, 10, 25, thisPanel, (HMENU)LBL_HST, instance, NULL);
    heroesHover = CreateWindow("static", ">", WS_CHILD | WS_VISIBLE, 80, 65, 10, 25, thisPanel, (HMENU)LBL_HHR, instance, NULL);
    positionsHover = CreateWindow("static", ">", WS_CHILD | WS_VISIBLE, 80, 115, 10, 25, thisPanel, (HMENU)LBL_HPS, instance, NULL);
    modesHover = CreateWindow("static", ">", WS_CHILD | WS_VISIBLE, 80, 165, 10, 25, thisPanel, (HMENU)LBL_HMD, instance, NULL);
    
    ShowWindow(statusHover, SW_HIDE);
    ShowWindow(heroesHover, SW_HIDE);
    ShowWindow(positionsHover, SW_HIDE);
    ShowWindow(modesHover, SW_HIDE);
    
    return thisPanel;
}

LRESULT CALLBACK SwapPanel::WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CTLCOLORSTATIC: return WMCtlColorStatic(wParam);
        case WM_PAINT: WMPaint(thisPanel); return false;
        case WM_LBUTTONUP: WMLeftMouseButtonUp(lParam); break;
        case WM_MOUSEMOVE: WMMouseMove(thisPanel); break;
        case WM_MOUSEHOVER: WMMouseHover(lParam); break;
        case WM_MOUSELEAVE: WMMouseLeave(); break;
        case WM_TIMER: WMTimer(thisPanel); break;
        default: return DefWindowProc(thisPanel, message, wParam, lParam);
    }
    
    return MainWindow::WindowProc(thisPanel, message, wParam, lParam);
}

LRESULT SwapPanel::WMCtlColorStatic(WPARAM wParam)
{
    HDC hdc = (HDC) wParam;
    SetTextColor(hdc, RGB(255,255,255));
    SetBkMode(hdc, TRANSPARENT);
    return (LRESULT)GetStockObject(NULL_BRUSH);
}

void SwapPanel::WMPaint(HWND thisPanel)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(thisPanel, &ps);
    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbm = CreateCompatibleBitmap(hdc, panelWidth, panelHeight);
    SelectObject(hdcBuffer, hbm);
    
    HBRUSH brush = CreateSolidBrush(RGB(35, 39, 42));
    
    FillRect(hdcBuffer, &background, brush);
    
    RECT highlightButton;
    
    switch(selectedButton)
    {
        case 0:
            highlightButton = statusButton;
            break;
        case 1:
            highlightButton = heroesButton;
            break;
        case 2:
            highlightButton = positionsButton;
            break;
            
        case 3:
            highlightButton = modesButton;
            break;
    }
    
    brush = CreateSolidBrush(RGB(150, 0, 0));
    
    FillRect(hdcBuffer, &highlightButton, brush);
    
    BitBlt(hdc, 0, 0, panelWidth, panelHeight, hdcBuffer, 0, 0, SRCCOPY);
    
    DeleteObject(brush);
    DeleteObject(hbm);
    DeleteDC(hdcBuffer);
    
    EndPaint(thisPanel, &ps);
}

void SwapPanel::WMLeftMouseButtonUp(LPARAM lParam)
{
    POINT mousePoint;
    mousePoint.x = LOWORD(lParam);
    mousePoint.y = HIWORD(lParam);
    
    if(PtInRect(&statusButton, mousePoint))
    {
        selectedButton = 0;
    }
    else if(PtInRect(&heroesButton, mousePoint))
    {
        selectedButton = 1;
    }
    else if(PtInRect(&positionsButton, mousePoint))
    {
        selectedButton = 2;
    }
    else if(PtInRect(&modesButton, mousePoint))
    {
        selectedButton = 3;
    }
}

void SwapPanel::WMMouseMove(HWND thisPanel)
{
    SetTimer(thisPanel, 10, 10, NULL);
    
    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(TRACKMOUSEEVENT);
    tme.dwFlags = TME_HOVER;
    tme.dwHoverTime = 10;
    tme.hwndTrack = thisPanel;
    TrackMouseEvent(&tme);
}

void SwapPanel::WMMouseHover(LPARAM lParam)
{
    POINT mousePoint;
    mousePoint.x = LOWORD(lParam);
    mousePoint.y = HIWORD(lParam);
    
    ShowWindow(statusHover, SW_HIDE);
    ShowWindow(heroesHover, SW_HIDE);
    ShowWindow(positionsHover, SW_HIDE);
    ShowWindow(modesHover, SW_HIDE);
    
    if(PtInRect(&statusButton, mousePoint) && selectedButton != 0)
    {
        buttonHover = 1;
        ShowWindow(statusHover, SW_SHOW);
    }
    else if(PtInRect(&heroesButton, mousePoint) && selectedButton != 1)
    {
        buttonHover = 2;
        ShowWindow(heroesHover, SW_SHOW);
    }
    else if(PtInRect(&positionsButton, mousePoint) && selectedButton != 2)
    {
        buttonHover = 3;
        ShowWindow(positionsHover, SW_SHOW);
    }
    else if(PtInRect(&modesButton, mousePoint) && selectedButton != 3)
    {
        buttonHover = 4;
        ShowWindow(modesHover, SW_SHOW);
    }
    else
    {
        buttonHover = 0;
    }
    
    if(buttonHover != currentButtonHover)
    {
        RedrawWindow(thisPanel, NULL, NULL, RDW_INVALIDATE);
        
        currentButtonHover = buttonHover;
    }
}

void SwapPanel::WMMouseLeave()
{
    if(buttonHover != 0)
    {
        buttonHover = 0;
        RedrawWindow(thisPanel, NULL, NULL, RDW_INVALIDATE);
        currentButtonHover = 0;
    }
}

void SwapPanel::WMTimer(HWND thisPanel)
{
    KillTimer(thisPanel, 100);
    
    RECT rc;
    POINT pt;
    
    GetWindowRect(thisPanel,&rc);
    GetCursorPos(&pt);

    mouseOver = PtInRect(&rc,pt);
    
    if(!mouseOver) PostMessage(thisPanel, WM_MOUSELEAVE, 0, 0L);
}

int SwapPanel::GetSelectedButton()
{
    return selectedButton;
}