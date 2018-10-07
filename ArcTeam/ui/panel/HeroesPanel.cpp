#include "HeroesPanel.h"
#include "../window/MainWindow.h"

HWND HeroesPanel::thisPanel;
HINSTANCE HeroesPanel::instance;
RECT HeroesPanel::background;
vector<Image*> HeroesPanel::images;

const vector<string> HeroesPanel::heroes {"placeholderOne"};
const int HeroesPanel::panelWidth = 900;
const int HeroesPanel::panelHeight = 550;

HWND HeroesPanel::Init(HWND parentWindow, HINSTANCE newInstance)
{
    instance = newInstance;
    thisPanel = CreateWindowEx(WS_EX_LEFT, "STATIC", NULL, WS_VISIBLE | WS_CHILD, 100, 20, panelWidth, panelHeight, parentWindow, (HMENU) PNL_ONE, NULL, NULL);
    SetRect(&background, 0, 0, panelWidth, panelHeight);
    
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(instance, szPath, MAX_PATH);
    string basePath = string(szPath);
    
    for(int i = 0; i < heroes.size(); i++)
    {
        string path = basePath.substr(0, basePath.length() - 11) + "resources\\images\\" + heroes[i] + ".png";
        
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        Image image(wcImagePath);
        
        images.push_back(image.GetThumbnailImage(200, 200, NULL, NULL));
    }
    
    CreateWindow("static", "Lakad Matataaaaag!", WS_CHILD | WS_VISIBLE, 375, 150, 200, 25, thisPanel, (HMENU)101, instance, NULL);
    CreateWindow("static", "I am still working on the heroes panel.", WS_CHILD | WS_VISIBLE, 315, 300, 400, 25, thisPanel, (HMENU)102, instance, NULL);
    
    ShowWindow(thisPanel, SW_HIDE);
    
    return thisPanel;
}

LRESULT CALLBACK HeroesPanel::WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CTLCOLORSTATIC: return WMCtlColorStatic(wParam);
        case WM_PAINT: WMPaint(thisPanel); return false;
        default: return DefWindowProc(thisPanel, message, wParam, lParam);
    }
    
    return MainWindow::WindowProc(thisPanel, message, wParam, lParam);
}

LRESULT HeroesPanel::WMCtlColorStatic(WPARAM wParam)
{
    HDC hdc = (HDC) wParam;
    SetTextColor(hdc, RGB(255,255,255));
    SetBkMode(hdc, TRANSPARENT);
    return (LRESULT)GetStockObject(NULL_BRUSH);
}

void HeroesPanel::WMPaint(HWND thisPanel)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(thisPanel, &ps);
    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbm = CreateCompatibleBitmap(hdc, panelWidth, panelHeight);
    SelectObject(hdcBuffer, hbm);
    
    HBRUSH brush = CreateSolidBrush(RGB(150, 0, 0));
    
    FillRect(hdcBuffer, &background, brush);
    
    DeleteObject(brush);

//    Graphics graphics(hdcBuffer);
//    
//    graphics.DrawImage(images[0], 0, 0, 200, 200);

    BitBlt(hdc, 0, 0, panelWidth, panelHeight, hdcBuffer, 0, 0, SRCCOPY);

    DeleteObject(hbm);
    DeleteDC(hdcBuffer);
    DeleteDC(hdc);

    EndPaint(thisPanel, &ps);
}

void HeroesPanel::RefreshPanel()
{
    RedrawWindow(thisPanel, NULL, NULL, RDW_INVALIDATE);
}

void HeroesPanel::HidePanel()
{
    ShowWindow(thisPanel, SW_HIDE);
}

void HeroesPanel::ShowPanel()
{
    ShowWindow(thisPanel, SW_SHOW);
}