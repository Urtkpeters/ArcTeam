#include "StatusPanel.h"
#include "MainWindow.h"

HWND StatusPanel::thisPanel;
HINSTANCE StatusPanel::instance;
RECT StatusPanel::background;
RECT StatusPanel::happyButton;
RECT StatusPanel::goodButton;
RECT StatusPanel::sadButton;
RECT StatusPanel::fineButton;
vector<Image*> StatusPanel::images;
vector<string> StatusPanel::statuses;
int StatusPanel::selectedButton;

const int StatusPanel::panelWidth = 100;
const int StatusPanel::panelHeight = 550;

HWND StatusPanel::Init(HWND parentWindow, HINSTANCE newInstance)
{
    instance = newInstance;
    thisPanel = CreateWindowEx(WS_EX_LEFT, "STATIC", NULL, WS_VISIBLE | WS_CHILD, 100, 20, panelWidth, panelHeight, parentWindow, (HMENU) 106, NULL, NULL);
    SetRect(&background, 0, 0, panelWidth, panelHeight);
    SetRect(&happyButton, 0, 0, panelWidth, 120);
    SetRect(&goodButton, 0, 120, panelWidth, 240);
    SetRect(&sadButton, 0, 240, panelWidth, 360);
    SetRect(&fineButton, 0, 360, panelWidth, 480);
    statuses = PlayerHandler::GetStatuses();
    selectedButton = 1;
    
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
    
    return thisPanel;
}

LRESULT CALLBACK StatusPanel::WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static HDC hdcBuffer;
    static PAINTSTRUCT ps;
    
    switch(message)
    {
        case WM_PAINT: WMPaint(thisPanel, hdc, hdcBuffer, ps); return false;
        case WM_LBUTTONUP: WMLeftMouseButtonUp(thisPanel, wParam, lParam); break;
        default: return DefWindowProc(thisPanel, message, wParam, lParam);
    }
    
    return MainWindow::WindowProc(thisPanel, message, wParam, lParam);
}

void StatusPanel::WMPaint(HWND thisPanel, HDC hdc, HDC hdcBuffer, PAINTSTRUCT ps)
{
    hdc = BeginPaint(thisPanel, &ps);
    hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbm = CreateCompatibleBitmap(hdc, panelWidth, panelHeight);
    SelectObject(hdcBuffer, hbm);

    HBRUSH brush = CreateSolidBrush(RGB(150, 0, 0));
    
    FillRect(hdcBuffer, &background, brush);

    Graphics graphics(hdcBuffer);

    for(int i = 1; i < statuses.size(); i++)
    {
        if(selectedButton == i)
        {
            brush = CreateSolidBrush(RGB(255, 255, 255));
            
            RECT selectedRect;
            
            switch(i)
            {
                case 1:
                    selectedRect = happyButton;
                    break;
                case 2:
                    selectedRect = goodButton;
                    break;
                case 3:
                    selectedRect = sadButton;
                    break;
                case 4:
                    selectedRect = fineButton;
                    break;
            }
            
            FillRect(hdcBuffer, &selectedRect, brush);
        }

        graphics.DrawImage(images[i], 10, 7 + ((i - 1) * 120), 80, 107);
    }

    BitBlt(hdc, 0, 0, panelWidth, panelHeight, hdcBuffer, 0, 0, SRCCOPY);
    DeleteObject(hbm);
    DeleteObject(brush);

    EndPaint(thisPanel, &ps);
    
    DeleteDC(hdcBuffer);
    DeleteDC(hdc);
}

void StatusPanel::WMLeftMouseButtonUp(HWND thisPanel, WPARAM wParam, LPARAM lParam)
{
    POINT mousePoint;
    mousePoint.x = LOWORD(lParam);
    mousePoint.y = HIWORD(lParam);
    
    if(PtInRect(&happyButton, mousePoint))
    {
        ChangeState(1);
    }
    else if(PtInRect(&goodButton, mousePoint))
    {
        ChangeState(2);
    }
    else if(PtInRect(&sadButton, mousePoint))
    {
        ChangeState(3);
    }
    else if(PtInRect(&fineButton, mousePoint))
    {
        ChangeState(4);
    }
}

void StatusPanel::ChangeState(int state)
{
    selectedButton = state;
    
    UserHandler::SetState(state);
    
    if(UserHandler::GetStateChange())
    {
        MainWindow::RefreshWindow();
    }
}

vector<Image*> StatusPanel::GetImages()
{
    return images;
}