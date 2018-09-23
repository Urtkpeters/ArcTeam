#include "PlayersPanel.h"
#include "MainWindow.h"

HWND PlayersPanel::thisPanel;
HINSTANCE PlayersPanel::instance;
RECT PlayersPanel::background;
vector<Image*> PlayersPanel::images;
vector<string> PlayersPanel::statuses;

const int PlayersPanel::panelWidth = 800;
const int PlayersPanel::panelHeight = 550;

HWND PlayersPanel::Init(HWND parentWindow, HINSTANCE newInstance)
{
    instance = newInstance;
    thisPanel = CreateWindowEx(WS_EX_LEFT, "STATIC", NULL, WS_VISIBLE | WS_CHILD, 200, 20, panelWidth, panelHeight, parentWindow, (HMENU) PNL_ONE, NULL, NULL);
    SetRect(&background, 0, 0, panelWidth, panelHeight);
    statuses = PlayerHandler::GetStatuses();
    
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(instance, szPath, MAX_PATH);
    string basePath = string(szPath);
    
    for(int i = 0; i < statuses.size(); i++)
    {
        string path = basePath.substr(0, basePath.length() - 11) + "resources\\images\\" + statuses[i] + ".jpg";
        
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        Image image(wcImagePath);
        
        images.push_back(image.GetThumbnailImage(715, 953, NULL, NULL));
    }
    
    vector<Player> players = PlayerHandler::GetPlayers();
    
    for(int i = 0; i < players.size(); i++)
    {
        int xPos = 40;
        int yPos = 240;
        
        if(i == 1 || i == 3) xPos = panelWidth - 130;
        if(i == 2 || i == 3) yPos = panelHeight - 240;
        
        players[i].CreateLabel(thisPanel, instance, LBL_ONE + i, xPos, yPos);
    }
    
    return thisPanel;
}

LRESULT CALLBACK PlayersPanel::WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static HDC hdcBuffer;
    static PAINTSTRUCT ps;
    
    switch(message)
    {
        case WM_CTLCOLORSTATIC: return WMCtlColorStatic(thisPanel, wParam, lParam, hdc);
        case WM_PAINT: WMPaint(thisPanel, hdc, hdcBuffer, ps); return false;
        default: return DefWindowProc(thisPanel, message, wParam, lParam);
    }
    
    return MainWindow::WindowProc(thisPanel, message, wParam, lParam);
}

LRESULT PlayersPanel::WMCtlColorStatic(HWND thisWindow, WPARAM wParam, LPARAM lParam, HDC hdc)
{
    hdc = (HDC) wParam;
    SetTextColor(hdc, RGB(255,255,255));
    SetBkMode(hdc, TRANSPARENT);
    return (LRESULT)GetStockObject(NULL_BRUSH);
}

void PlayersPanel::WMPaint(HWND thisPanel, HDC hdc, HDC hdcBuffer, PAINTSTRUCT ps)
{
    vector<Player> players = PlayerHandler::GetPlayers();
    
    hdc = BeginPaint(thisPanel, &ps);
    hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbm = CreateCompatibleBitmap(hdc, panelWidth, panelHeight);
    SelectObject(hdcBuffer, hbm);

    HBRUSH brush = CreateSolidBrush(RGB(58, 61, 66));

    FillRect(hdcBuffer, &background, brush);

    DeleteObject(brush);

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

        if(i == 1 || i == 3) xPos = panelWidth - 180;
        if(i == 2 || i == 3) yPos = panelHeight - 230;

        graphics.DrawImage(thumbnail, xPos, yPos, 200, 266);
    }

    BitBlt(hdc, 0, 0, panelWidth, panelHeight, hdcBuffer, 0, 0, SRCCOPY);

    DeleteObject(hbm);
    DeleteDC(hdcBuffer);
    DeleteDC(hdc);

    EndPaint(thisPanel, &ps);
}