#include "PlayersPanel.h"
#include "MainWindow.h"

HWND PlayersPanel::thisPanel;
HINSTANCE PlayersPanel::instance;
RECT PlayersPanel::background;
vector<Image*> PlayersPanel::images;

const int PlayersPanel::panelWidth = 400;
const int PlayersPanel::panelHeight = 400;

HWND PlayersPanel::Init(HWND parentWindow, HINSTANCE newInstance, vector<Image*> newImages)
{
    instance = newInstance;
    thisPanel = CreateWindowEx(WS_EX_LEFT, "STATIC", NULL, WS_VISIBLE | WS_CHILD, 100, 20, panelWidth, panelHeight, parentWindow, (HMENU) 106, NULL, NULL);
    SetRect(&background, 0, 0, panelWidth, panelHeight);
    images = newImages;
    
    return thisPanel;
}

LRESULT CALLBACK PlayersPanel::WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam)
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

void PlayersPanel::WMPaint(HWND thisPanel, HDC hdc, HDC hdcBuffer, PAINTSTRUCT ps)
{
    hdc = BeginPaint(thisPanel, &ps);
    hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbm = CreateCompatibleBitmap(hdc, panelWidth, panelHeight);
    SelectObject(hdcBuffer, hbm);
    
    HBRUSH brush = CreateSolidBrush(RGB(87, 112, 153));
    
    FillRect(hdcBuffer, &background, brush);
    
    DeleteObject(brush);
    
    vector<Player> players = PlayerHandler::GetPlayers();
    vector<string> statuses = PlayerHandler::GetStatuses();
    
    Graphics graphics(hdcBuffer);
    
    for(int i = 0; i < players.size(); i++)
    {
        string newStatus = players[i].GetStatus();
        
        Image* thumbnail;

        for(int j = 0; j < statuses.size(); j++)
        {
            if(statuses[j] == newStatus)
            {
                thumbnail = images[j];
            }
        }

        int xPos = -14;
        int yPos = -15;

        if(i == 1 || i == 3) xPos = 315;
        if(i == 2 || i == 3) yPos = 282;

        graphics.DrawImage(thumbnail, xPos, yPos, 100, 133);
    }
    
    BitBlt(hdc, 0, 0, panelWidth, panelHeight, hdcBuffer, 0, 0, SRCCOPY);
    
    DeleteObject(hbm);
    DeleteDC(hdcBuffer);
    
    EndPaint(thisPanel, &ps);
}