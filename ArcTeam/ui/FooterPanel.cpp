#include "FooterPanel.h"
#include "MainWindow.h"

HWND FooterPanel::thisPanel;
HINSTANCE FooterPanel::instance;
vector<Image*> FooterPanel::images;
int FooterPanel::displayImage;
int FooterPanel::oldDisplayImage;
bool FooterPanel::mouseOver;
RECT FooterPanel::dotaRect;
RECT FooterPanel::heroesRect;
RECT FooterPanel::positionsRect;
RECT FooterPanel::modesRect;

const int FooterPanel::panelWidth = 750;
const int FooterPanel::panelHeight = 75;
const vector<string> FooterPanel::imageNames {"Default", "Dota", "Heroes", "Positions", "Modes"};

HWND FooterPanel::Init(HWND parentWindow, HINSTANCE newInstance)
{
    instance = newInstance;
    thisPanel = CreateWindowEx(WS_EX_LEFT, "STATIC", NULL, WS_VISIBLE | WS_CHILD, 0, 515, panelWidth, panelHeight, parentWindow, (HMENU) 106, NULL, NULL);
    
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(instance, szPath, MAX_PATH);
    string basePath = string(szPath);
    
    for(int i = 0; i < imageNames.size(); i++)
    {
        string path = basePath.substr(0, basePath.length() - 11) + "resources\\images\\footerBar" + imageNames[i] + ".png";
        
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        
        Image image(wcImagePath);
        
        image.GetThumbnailImage(panelWidth, panelHeight, NULL, NULL);
        images.push_back(image.GetThumbnailImage(panelWidth, panelHeight, NULL, NULL));
    }
    
    displayImage = 0;
    oldDisplayImage = -1;
    
    SetRect(&dotaRect, 45, 0, 170, 75);
    SetRect(&heroesRect, 170, 20, 320, 65);
    SetRect(&positionsRect, 320, 20, 560, 65);
    SetRect(&modesRect, 560, 20, 750, 65);
    
    return thisPanel;
}

LRESULT CALLBACK FooterPanel::WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static HDC hdcBuffer;
    static PAINTSTRUCT ps;
    
    switch(message)
    {
        case WM_ERASEBKGND: return true;
        case WM_TIMER: WMTimer(thisPanel); break;
        case WM_PAINT: WMPaint(thisPanel, hdc, hdcBuffer, ps); return false;
        case WM_MOUSEMOVE: WMMouseMove(thisPanel); break;
        case WM_MOUSEHOVER: WMMouseHover(thisPanel, lParam); break;
        case WM_MOUSELEAVE: WMMouseLeave(); break;
        default: return DefWindowProc(thisPanel, message, wParam, lParam);
    }
    
    return MainWindow::WindowProc(thisPanel, message, wParam, lParam);
}

void FooterPanel::WMPaint(HWND thisPanel, HDC hdc, HDC hdcBuffer, PAINTSTRUCT ps)
{
    hdc = BeginPaint(thisPanel, &ps);
    hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbm = CreateCompatibleBitmap(hdc, panelWidth, panelHeight);
    SelectObject(hdcBuffer, hbm);
    
    Graphics graphics(hdcBuffer);
    
    graphics.DrawImage(images[displayImage], 0, 0, panelWidth, panelHeight);
    
    BitBlt(hdc, 0, 0, panelWidth, panelHeight, hdcBuffer, 0, 0, SRCCOPY);
    
    DeleteObject(hbm);
    DeleteDC(hdcBuffer);
    
    EndPaint(thisPanel, &ps);
}

void FooterPanel::WMMouseMove(HWND thisPanel)
{
    SetTimer(thisPanel, 10, 10, NULL);
    
    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(TRACKMOUSEEVENT);
    tme.dwFlags = TME_HOVER;
    tme.dwHoverTime = 10;
    tme.hwndTrack = thisPanel;
    TrackMouseEvent(&tme);
}

void FooterPanel::WMMouseHover(HWND thisPanel, LPARAM lParam)
{
    POINT mousePoint;
    mousePoint.x = LOWORD(lParam);
    mousePoint.y = HIWORD(lParam);
    
    if(PtInRect(&dotaRect, mousePoint))
    {
        displayImage = 1;
    }
    else if(PtInRect(&heroesRect, mousePoint))
    {
        displayImage = 2;
    }
    else if(PtInRect(&positionsRect, mousePoint))
    {
        displayImage = 3;
    }
    else if(PtInRect(&modesRect, mousePoint))
    {
        displayImage = 4;
    }
    else
    {
        displayImage = 0;
    }
    
    if(displayImage != oldDisplayImage)
    {
        MainWindow::RefreshWindow();
        
        oldDisplayImage = displayImage;
    }
}

void FooterPanel::WMMouseLeave()
{
    if(displayImage != 0)
    {
        displayImage = 0;
        MainWindow::RefreshWindow();
        oldDisplayImage = 0;
    }
}

void FooterPanel::WMTimer(HWND thisPanel)
{
    KillTimer(thisPanel, 100);
    
    RECT rc;
    POINT pt;
    
    GetWindowRect(thisPanel,&rc);
    GetCursorPos(&pt);

    mouseOver = PtInRect(&rc,pt);
    
    if(!mouseOver) PostMessage(thisPanel, WM_MOUSELEAVE, 0, 0L);
}