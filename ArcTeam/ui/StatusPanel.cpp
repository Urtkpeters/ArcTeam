#include "StatusPanel.h"
#include "MainWindow.h"

HWND StatusPanel::thisPanel;
HINSTANCE StatusPanel::instance;
RECT StatusPanel::background;
vector<Image*> StatusPanel::images;
vector<string> StatusPanel::statuses;

const int StatusPanel::panelWidth = 100;
const int StatusPanel::panelHeight = 550;

HWND StatusPanel::Init(HWND parentWindow, HINSTANCE newInstance)
{
    instance = newInstance;
    thisPanel = CreateWindowEx(WS_EX_LEFT, "STATIC", NULL, WS_VISIBLE | WS_CHILD, 100, 20, panelWidth, panelHeight, parentWindow, (HMENU) 106, NULL, NULL);
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
    
    return thisPanel;
}

LRESULT CALLBACK StatusPanel::WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static HDC hdcBuffer;
    static PAINTSTRUCT ps;
    
    switch(message)
    {
        case WM_LBUTTONUP: WMLeftMouseButtonUp(thisPanel, wParam, lParam); break;
        case WM_PAINT: WMPaint(thisPanel, hdc, hdcBuffer, ps); return false;
        default: return DefWindowProc(thisPanel, message, wParam, lParam);
    }
    
    return MainWindow::WindowProc(thisPanel, message, wParam, lParam);
}

void StatusPanel::WMLeftMouseButtonUp(HWND thisPanel, WPARAM wParam, LPARAM lParam)
{
    int mPosX = LOWORD(lParam);
    int mPosY = HIWORD(lParam);
    
    if(mPosX > 500 && mPosY < 20)
    {
        PostMessage(thisPanel, WM_CLOSE, 0, 0);
    }
    
    if(mPosX > 90 && mPosX < 240)
    {
        // Happy
        if(mPosY > 210 && mPosY < 410)
        {
            ChangeState(1);
        }
        
        // Sad
        if(mPosY > 450 && mPosY < 650)
        {
            ChangeState(3);
        }
    }
    
    if(mPosX > 290 && mPosX < 440)
    {
        // Good
        if(mPosY > 210 && mPosY < 410)
        {
            ChangeState(2);
        }
        
        // Fine
        if(mPosY > 450 && mPosY < 650)
        {
            ChangeState(4);
        }
    }
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
//        int state = UserHandler::GetState();
//        int lastState = UserHandler::GetLastState();
//
//        if(i == state || i == lastState || lastState == 0)
//        {
//            RECT bknd;
//            brush = CreateSolidBrush(RGB(240, 240, 240));
//
//            if(state == i)
//            {
//                brush = CreateSolidBrush(RGB(198, 0, 0));
//            }
//
//            SetRect(&bknd, xPos - 10, yPos - 10, xPos + 160, yPos + 210);
//            FillRect(mainHDC, &bknd, brush);
//            DeleteObject(brush);

            graphics.DrawImage(images[i], 10, 30 + ((i - 1) * 120), 80, 107);
//        }
    }

    BitBlt(hdc, 0, 0, panelWidth, panelHeight, hdcBuffer, 0, 0, SRCCOPY);
    DeleteObject(hbm);
    DeleteObject(brush);

    EndPaint(thisPanel, &ps);
    
    DeleteDC(hdcBuffer);
    DeleteDC(hdc);
}

void StatusPanel::ChangeState(int state)
{
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