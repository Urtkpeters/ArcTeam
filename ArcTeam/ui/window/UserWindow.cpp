#include "UserWindow.h"
#include "WindowManager.h"

RECT UserWindow::titleBar;
RECT UserWindow::closeButton;
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

const vector<string> UserWindow::imageNames {"close", "close_hover", "avatar1", "avatar2", "avatar3", "avatar4", "avatar5"};
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
    SetRect(&closeButton, windowWidth - 20, 0, windowWidth, 20);
    SetRect(&background, 0, 20, windowWidth, windowHeight);
    SetRect(&oneButton, 5, 100, 105, 220);
    SetRect(&twoButton, 127, 100, 227, 220);
    SetRect(&threeButton, 249, 100, 349, 220);
    SetRect(&fourButton, 371, 100, 471, 220);
    SetRect(&fiveButton, 493, 100, 595, 220);
    
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(instance, szPath, MAX_PATH);
    string basePath = string(szPath);
    
    for(int i = 0; i < imageNames.size(); i++)
    {
        int imgSize = 20;
        string path = basePath.substr(0, basePath.length() - 11) + "resources\\images\\" + imageNames[i] + ".png";
        
        DWORD ftyp = GetFileAttributesA(path.c_str());
    
        if(ftyp == INVALID_FILE_ATTRIBUTES)
        {
            path = basePath.substr(0, basePath.length() - 11) + "resources\\images\\" + imageNames[i] + ".jpg";
            imgSize = 50;
        }
        
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        
        Image image(wcImagePath);
        
        image.GetThumbnailImage(imgSize, imgSize, NULL, NULL);
        images.push_back(image.GetThumbnailImage(imgSize, imgSize, NULL, NULL));
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
    
    graphics.DrawImage(images[buttonHover], userWindowWidth-20, 0, 20, 20);
    
    for(int i = 2; i < images.size(); i++)
    {
        graphics.DrawImage(images[i], 30 + ((i - 2) * 122), 120, 50, 50);
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
        PostMessage(thisWindow, WM_CLOSE, 0, 0);
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
    RECT oneRect;
    RECT twoRect;
    RECT threeRect;
    RECT fourRect;
    RECT fiveRect;
    POINT mousePoint;
    
    GetWindowRect(thisWindow,&windowRect);
    GetCursorPos(&mousePoint);
    
    closeRect = windowRect;
    
    closeRect.left = closeRect.left + userWindowWidth - 20;
    closeRect.bottom = closeRect.bottom - userWindowHeight + 20;

    if(!PtInRect(&closeRect, mousePoint)) PostMessage(thisWindow, WM_MOUSELEAVE, 0, 0L); return;
    
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

    if(PtInRect(&titleBar, mousePoint) && mousePoint.x < titleBar.right - 20)
    {
        hit = HTCAPTION;
    }

    return hit;
}

void UserWindow::CreateComponents()
{
    CreateChildLabel("ArcTeam", 5, 3, thisWindow, LBL_TITLE);
    CreateWindow("static", "Choose User", WS_CHILD | WS_VISIBLE | SS_CENTER, (userWindowWidth / 2) - 50, 75, 100, 25, thisWindow, (HMENU)LBL_USR, instance, NULL);
    
    vector<string> usernames = UserHandler::GetUsers();
    
    for(int i = 0; i < usernames.size(); i++)
    {
        CreateWindow("static", usernames[i].c_str(), WS_CHILD | WS_VISIBLE | SS_CENTER, 7 + (i * 122), 180, 100, 25, thisWindow, (HMENU)LBL_ONE + i, instance, NULL);
    }
}