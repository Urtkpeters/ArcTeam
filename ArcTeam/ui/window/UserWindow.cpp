#include "UserWindow.h"
#include "WindowManager.h"

RECT UserWindow::titleBar;
RECT UserWindow::grabBar;
RECT UserWindow::closeButton;
RECT UserWindow::minimizeButton;
RECT UserWindow::oneButton;
RECT UserWindow::twoButton;
RECT UserWindow::threeButton;
RECT UserWindow::fourButton;
RECT UserWindow::fiveButton;
RECT UserWindow::background;
vector<Image*> UserWindow::images;
int UserWindow::buttonHover;
int UserWindow::currentButtonHover;
int UserWindow::playerButtonHover = 0;
int UserWindow::currentPlayerHover = 0;

const vector<string> UserWindow::imageNames {"logo", "close", "close_hover", "minimize", "minimize_hover", "avatar1", "avatar2", "avatar3", "avatar4", "avatar5"};
const int UserWindow::userWindowWidth = 600;
const int UserWindow::userWindowHeight = 300;

MSG UserWindow::CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow)
{
    wc.lpfnWndProc = WindowProc;
    strClassName = "userWindow";
    windowTitle = "ArcTeam v" + applicationVersion;
    windowWidth = userWindowWidth;
    windowHeight = userWindowHeight;
    windowStartX = (GetSystemMetrics(0) / 2) - (windowWidth / 2);
    windowStartY = (GetSystemMetrics(1) / 2) - (windowHeight / 2);
    buttonHover = 0;
    currentButtonHover = -1;
    
    SetRect(&titleBar, 0, 0, windowWidth, 20);
    SetRect(&grabBar, 0, 0, windowWidth - 80, 20);
    SetRect(&closeButton, windowWidth - 40, 0, windowWidth, 20);
    SetRect(&minimizeButton, windowWidth - 80, 0, windowWidth - 40, 20);
    SetRect(&background, 0, 20, windowWidth, windowHeight);
    SetRect(&oneButton, 5, 100, 105, 220);
    SetRect(&twoButton, 127, 100, 227, 220);
    SetRect(&threeButton, 249, 100, 349, 220);
    SetRect(&fourButton, 371, 100, 471, 220);
    SetRect(&fiveButton, 493, 100, 595, 220);
    
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(instance, szPath, MAX_PATH);
    string basePath = string(szPath);
    string baseDirectory = basePath.substr(0, basePath.length() - 11);
    
    for(int i = 0; i < imageNames.size(); i++)
    {
        int imgX = 20;
        int imgY = 20;
        
        if(imageNames[i] == "logo")
        {
            imgX = 100;
            imgY = 18;
        }
        else if(i > 4)
        {
            imgX = 50;
            imgY = 50;
        }
    
        string path = baseDirectory + "resources\\images\\" + imageNames[i] + ".png";
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        
        Image image(wcImagePath);
        
        image.GetThumbnailImage(imgX, imgY, NULL, NULL);
        images.push_back(image.GetThumbnailImage(imgX, imgY, NULL, NULL));
    }
    
    return GenericWindow::CreateNewWindow(Msg, hInstance, nCmdShow);
}

LRESULT CALLBACK UserWindow::WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CTLCOLORSTATIC: return WMCtlColorStatic(wParam);
        case WM_PAINT: WMPaint(thisWindow); break;
        case WM_LBUTTONUP: WMLeftMouseButtonUp(thisWindow, lParam); break;
        case WM_MOUSEMOVE: WMMouseMove(thisWindow); break;
        case WM_MOUSEHOVER: WMMouseHover(thisWindow, lParam); break;
        case WM_MOUSELEAVE: WMMouseLeave(thisWindow, wParam); break;
        case WM_TIMER: WMTimer(thisWindow); break;
        case WM_NCHITTEST: return NCHitTest(thisWindow, lParam);
        case WM_CLOSE: DestroyWindow(thisWindow); break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(thisWindow, message, wParam, lParam);
    }
    
    return 0;
}

LRESULT UserWindow::WMCtlColorStatic(WPARAM wParam)
{
    HDC hdc = (HDC) wParam;
    SetTextColor(hdc, RGB(255,255,255));
    SetBkMode(hdc, TRANSPARENT);
    return (LRESULT)GetStockObject(NULL_BRUSH);
}

void UserWindow::WMPaint(HWND thisWindow)
{
    PAINTSTRUCT ps;
    HDC mainHDC;
    HDC bufferHDC;
    HBITMAP hbm;
    int closeImage = 1;
    int minimizeImage = 3;
    
    if(buttonHover == 1)
    {
        closeImage = 2;
    }
    else if(buttonHover == 2)
    {
        minimizeImage = 4;
    }
    
    mainHDC = BeginPaint(thisWindow, &ps);
    bufferHDC = CreateCompatibleDC(mainHDC);
    hbm = CreateCompatibleBitmap(mainHDC, userWindowWidth, userWindowHeight);
    SelectObject(bufferHDC, hbm);
    
    HBRUSH brush = CreateSolidBrush(RGB(35, 39, 42));
    FillRect(bufferHDC, &titleBar, brush);
    
    brush = CreateSolidBrush(RGB(58, 61, 66));
    FillRect(bufferHDC, &background, brush);
    
    brush = CreateSolidBrush(RGB(35, 39, 42));
    
    switch(playerButtonHover)
    {
        case 1:
            FillRect(bufferHDC, &oneButton, brush);
            break;
        case 2:
            FillRect(bufferHDC, &twoButton, brush);
            break;
            
        case 3:
            FillRect(bufferHDC, &threeButton, brush);
            break;
            
        case 4:
            FillRect(bufferHDC, &fourButton, brush);
            break;
        case 5:
            FillRect(bufferHDC, &fiveButton, brush);
            break;
    }
    
    Graphics graphics(bufferHDC);
    
    graphics.DrawImage(images[0], 2, 0, 100, 18);
    graphics.DrawImage(images[closeImage], userWindowWidth-30, 0, 20, 20);
    graphics.DrawImage(images[minimizeImage], userWindowWidth-70, 0, 20, 20);
    
    for(int i = 5; i < images.size(); i++)
    {
        graphics.DrawImage(images[i], 30 + ((i - 5) * 122), 120, 50, 50);
    }
    
    BitBlt(mainHDC, 0, 0, userWindowWidth, userWindowHeight, bufferHDC, 0, 0, SRCCOPY);
    
    DeleteObject(hbm);
    DeleteDC(bufferHDC);
    DeleteDC(mainHDC);

    DeleteObject(brush);
    EndPaint(thisWindow, &ps);
}

void UserWindow::WMLeftMouseButtonUp(HWND thisWindow, LPARAM lParam)
{
    POINT mousePoint;
    mousePoint.x = LOWORD(lParam);
    mousePoint.y = HIWORD(lParam);
    
    if(PtInRect(&closeButton, mousePoint))
    {
        PostMessage(thisWindow, WM_SYSCOMMAND, SC_CLOSE, 0);
        return;
    }
    
    if(PtInRect(&minimizeButton, mousePoint))
    {
        PostMessage(thisWindow, WM_SYSCOMMAND, SC_MINIMIZE, 0);
        return;
    }
    
    vector<string> usernames = UserHandler::GetUsers();
    
    if(PtInRect(&oneButton, mousePoint)) UserHandler::SetUsername(usernames[0]);
    else if(PtInRect(&twoButton, mousePoint)) UserHandler::SetUsername(usernames[1]);
    else if(PtInRect(&threeButton, mousePoint)) UserHandler::SetUsername(usernames[2]);
    else if(PtInRect(&fourButton, mousePoint)) UserHandler::SetUsername(usernames[3]);
    else if(PtInRect(&fiveButton, mousePoint)) UserHandler::SetUsername(usernames[4]);
    
    if(UserHandler::GetUsername() != "")
    {
        WindowManager::SetWindow("mainWindow");
        PostMessage(thisWindow, WM_CLOSE, 0, 0);
    }
}

void UserWindow::WMMouseMove(HWND thisWindow)
{
    SetTimer(thisWindow, 10, 10, NULL);
    
    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(TRACKMOUSEEVENT);
    tme.dwFlags = TME_HOVER;
    tme.dwHoverTime = 10;
    tme.hwndTrack = thisWindow;
    TrackMouseEvent(&tme);
}

void UserWindow::WMMouseHover(HWND thisWindow, LPARAM lParam)
{
    POINT mousePoint;
    mousePoint.x = LOWORD(lParam);
    mousePoint.y = HIWORD(lParam);
    
    if(PtInRect(&closeButton, mousePoint))
    {
        buttonHover = 1;
    }
    else if(PtInRect(&minimizeButton, mousePoint))
    {
        buttonHover = 2;
    }
    else
    {
        buttonHover = 0;
    }
    
    if(PtInRect(&oneButton, mousePoint))
    {
        playerButtonHover = 1;
    }
    else if(PtInRect(&twoButton, mousePoint))
    {
        playerButtonHover = 2;
    }
    else if(PtInRect(&threeButton, mousePoint))
    {
        playerButtonHover = 3;
    }
    else if(PtInRect(&fourButton, mousePoint))
    {
        playerButtonHover = 4;
    }
    else if(PtInRect(&fiveButton, mousePoint))
    {
        playerButtonHover = 5;
    }
    else
    {
        playerButtonHover = 0;
    }
    
    if(buttonHover != currentButtonHover)
    {
        RedrawWindow(thisWindow, NULL, NULL, RDW_INVALIDATE);
        
        currentButtonHover = buttonHover;
    }
    
    if(playerButtonHover != currentPlayerHover)
    {
        RedrawWindow(thisWindow, NULL, NULL, RDW_INVALIDATE);
        
        currentPlayerHover = playerButtonHover;
    }
}

void UserWindow::WMMouseLeave(HWND thisWindow, WPARAM wParam)
{
    if(buttonHover != 0 && wParam == 0)
    {
        buttonHover = 0;
        RedrawWindow(thisWindow, NULL, NULL, RDW_INVALIDATE);
        currentButtonHover = 0;
    }
    
    if(playerButtonHover != 0 && wParam == 1)
    {
        playerButtonHover = 0;
        RedrawWindow(thisWindow, NULL, NULL, RDW_INVALIDATE);
        currentPlayerHover = 0;
    }
}

void UserWindow::WMTimer(HWND thisWindow)
{
    KillTimer(thisWindow, 100);
    
    RECT windowRect;
    RECT closeRect;
    RECT minimizeRect;
    RECT oneRect;
    RECT twoRect;
    RECT threeRect;
    RECT fourRect;
    RECT fiveRect;
    POINT mousePoint;
    
    GetWindowRect(thisWindow,&windowRect);
    GetCursorPos(&mousePoint);
    
    closeRect = windowRect;
    
    closeRect.left = closeRect.left + userWindowWidth - 40;
    closeRect.bottom = closeRect.bottom - userWindowHeight + 20;

    minimizeRect = windowRect;
    
    minimizeRect.left = minimizeRect.left + userWindowWidth - 80;
    minimizeRect.right = minimizeRect.right - 40;
    minimizeRect.bottom = minimizeRect.bottom - userWindowHeight + 20;

    if(!PtInRect(&closeRect, mousePoint) && !PtInRect(&minimizeRect, mousePoint)) PostMessage(thisWindow, WM_MOUSELEAVE, 0, 0L); return;
    
    oneRect = windowRect;
    
    oneRect.left = oneRect.left + oneButton.left;
    oneRect.top = oneRect.top + oneButton.top;
    oneRect.right = (oneRect.right - userWindowWidth) + oneButton.right;
    oneRect.bottom = (oneRect.bottom - userWindowHeight) + oneButton.bottom;
    
    if(!PtInRect(&oneRect, mousePoint)) PostMessage(thisWindow, WM_MOUSELEAVE, 1, 0L); return;
    
    twoRect = windowRect;
    
    twoRect.left = twoRect.left + twoButton.left;
    twoRect.top = twoRect.top + twoButton.top;
    twoRect.right = (twoRect.right - userWindowWidth) + twoButton.right;
    twoRect.bottom = (twoRect.bottom - userWindowHeight) + twoButton.bottom;
    
    if(!PtInRect(&twoRect, mousePoint)) PostMessage(thisWindow, WM_MOUSELEAVE, 1, 0L); return;
    
    threeRect = windowRect;
    
    threeRect.left = threeRect.left + threeButton.left;
    threeRect.top = threeRect.top + threeButton.top;
    threeRect.right = (threeRect.right - userWindowWidth) + threeButton.right;
    threeRect.bottom = (threeRect.bottom - userWindowHeight) + threeButton.bottom;
    
    if(!PtInRect(&threeRect, mousePoint)) PostMessage(thisWindow, WM_MOUSELEAVE, 1, 0L); return;
    
    fourRect = windowRect;
    
    fourRect.left = fourRect.left + fourButton.left;
    fourRect.top = fourRect.top + fourButton.top;
    fourRect.right = (fourRect.right - userWindowWidth) + fourButton.right;
    fourRect.bottom = (fourRect.bottom - userWindowHeight) + fourButton.bottom;
    
    if(!PtInRect(&fourRect, mousePoint)) PostMessage(thisWindow, WM_MOUSELEAVE, 1, 0L); return;
    
    fiveRect = windowRect;
    
    fiveRect.left = fiveRect.left + fiveButton.left;
    fiveRect.top = fiveRect.top + fiveButton.top;
    fiveRect.right = (fiveRect.right - userWindowWidth) + fiveButton.right;
    fiveRect.bottom = (fiveRect.bottom - userWindowHeight) + fiveButton.bottom;
    
    if(!PtInRect(&fiveRect, mousePoint)) PostMessage(thisWindow, WM_MOUSELEAVE, 1, 0L); return;
}

LRESULT UserWindow::NCHitTest(HWND thisWindow, LPARAM lParam)
{
    LRESULT hit = HTCLIENT;
    POINT mousePoint;

    mousePoint.x = LOWORD(lParam);
    mousePoint.y = HIWORD(lParam);

    ScreenToClient(thisWindow, &mousePoint);

    if(PtInRect(&grabBar, mousePoint))
    {
        hit = HTCAPTION;
    }

    return hit;
}

void UserWindow::CreateComponents()
{
    CreateWindow("static", "Choose User", WS_CHILD | WS_VISIBLE | SS_CENTER, (userWindowWidth / 2) - 50, 75, 100, 25, thisWindow, (HMENU)LBL_USR, instance, NULL);
    
    vector<string> usernames = UserHandler::GetUsers();
    
    for(int i = 0; i < usernames.size(); i++)
    {
        CreateWindow("static", usernames[i].c_str(), WS_CHILD | WS_VISIBLE | SS_CENTER, 7 + (i * 122), 180, 100, 25, thisWindow, (HMENU)LBL_ONE + i, instance, NULL);
    }
}