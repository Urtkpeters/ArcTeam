#include "StatusPanel.h"
#include "../window/MainWindow.h"

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
    SetRect(&happyButton, 0, 0, panelWidth, 95);
    SetRect(&goodButton, 0, 95, panelWidth, 190);
    SetRect(&sadButton, 0, 190, panelWidth, 285);
    SetRect(&fineButton, 0, 285, panelWidth, 380);
    statuses = PlayerHandler::GetStatuses();
    selectedButton = 1;
    
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(instance, szPath, MAX_PATH);
    string basePath = string(szPath);
    string baseDirectory = basePath.substr(0, basePath.length() - 11);
    
    for(int i = 0; i < statuses.size(); i++)
    {
        string path = baseDirectory + "resources\\images\\" + statuses[i] + ".png";
        
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        Image image(wcImagePath);
        
        images.push_back(image.GetThumbnailImage(80, 80, NULL, NULL));
    }
    
    for(int i = 1; i < statuses.size(); i++)
    {
        string path = baseDirectory + "resources\\images\\" + statuses[i] + "_selected.png";
        
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        Image image(wcImagePath);
        cout << path << endl;
        images.push_back(image.GetThumbnailImage(80, 80, NULL, NULL));
    }
    
    return thisPanel;
}

LRESULT CALLBACK StatusPanel::WindowProc(HWND thisPanel, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_PAINT: WMPaint(thisPanel); return false;
        case WM_LBUTTONUP: WMLeftMouseButtonUp(thisPanel, lParam); break;
        default: return DefWindowProc(thisPanel, message, wParam, lParam);
    }
    
    return MainWindow::WindowProc(thisPanel, message, wParam, lParam);
}

void StatusPanel::WMPaint(HWND thisPanel)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(thisPanel, &ps);
    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbm = CreateCompatibleBitmap(hdc, panelWidth, panelHeight);
    SelectObject(hdcBuffer, hbm);

    HBRUSH brush = CreateSolidBrush(RGB(150, 0, 0));
    
    FillRect(hdcBuffer, &background, brush);

    Graphics graphics(hdcBuffer);

    for(int i = 1; i < statuses.size(); i++)
    {
        int selectedOption = i;
        
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
            
            selectedOption += 4;
        }
        
        graphics.DrawImage(images[selectedOption], 10, 7 + ((i - 1) * 95), 80, 80);
    }

    BitBlt(hdc, 0, 0, panelWidth, panelHeight, hdcBuffer, 0, 0, SRCCOPY);
    
    DeleteObject(hbm);
    DeleteObject(brush);

    EndPaint(thisPanel, &ps);
    
    DeleteDC(hdcBuffer);
    DeleteDC(hdc);
}

void StatusPanel::WMLeftMouseButtonUp(HWND thisPanel, LPARAM lParam)
{
    POINT mousePoint;
    mousePoint.x = LOWORD(lParam);
    mousePoint.y = HIWORD(lParam);
    
    if(PtInRect(&happyButton, mousePoint))
    {
        ChangeState(thisPanel, 1);
    }
    else if(PtInRect(&goodButton, mousePoint))
    {
        ChangeState(thisPanel, 2);
    }
    else if(PtInRect(&sadButton, mousePoint))
    {
        ChangeState(thisPanel, 3);
    }
    else if(PtInRect(&fineButton, mousePoint))
    {
        ChangeState(thisPanel, 4);
    }
}

void StatusPanel::ChangeState(HWND thisPanel, int state)
{
    selectedButton = state;
    
    UserHandler::SetState(state);
    
    if(UserHandler::GetStateChange())
    {
        RedrawWindow(thisPanel, NULL, NULL, RDW_INVALIDATE);
    }
}

vector<Image*> StatusPanel::GetImages()
{
    return images;
}