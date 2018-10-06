#include "MainWindow.h"

RECT MainWindow::background;
HWND MainWindow::mainWindow;
HWND MainWindow::errorLabel;
vector<Image*> MainWindow::images;
RECT MainWindow::closeButton;
RECT MainWindow::minimizeButton;
RECT MainWindow::grabBar;
int MainWindow::buttonHover;
int MainWindow::currentButtonHover;


const vector<string> MainWindow::imageNames {"logo", "close", "close_hover", "minimize", "minimize_hover"};
const int MainWindow::mainWindowWidth = 1000;
const int MainWindow::mainWindowHeight = 570;

MSG MainWindow::CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow)
{
    wc.lpfnWndProc = WindowProc;
    strClassName = "mainWindow";
    windowTitle = "ArcTeam v" + applicationVersion;
    windowStartX = 100;
    windowStartY = 100;
    windowWidth = mainWindowWidth;
    windowHeight = mainWindowHeight;
    buttonHover = 0;
    currentButtonHover = -1;
    
    SetRect(&background, 0, 0, mainWindowWidth, 20);
    SetRect(&closeButton, mainWindowWidth - 40, 0, mainWindowWidth, 20);
    SetRect(&minimizeButton, mainWindowWidth - 80, 0, mainWindowWidth - 40, 20);
    SetRect(&grabBar, 0, 0, mainWindowWidth - 80, mainWindowHeight);
    
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(instance, szPath, MAX_PATH);
    string basePath = string(szPath);
    
    for(int i = 0; i < imageNames.size(); i++)
    {
        int imgX = 20;
        int imgY = 20;
        
        if(imageNames[i] == "logo")
        {
            imgX = 100;
            imgY = 18;
        }
        
        string path = basePath.substr(0, basePath.length() - 11) + "resources\\images\\" + imageNames[i] + ".png";
        
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        
        Image image(wcImagePath);
        
        image.GetThumbnailImage(imgX, imgY, NULL, NULL);
        images.push_back(image.GetThumbnailImage(imgX, imgY, NULL, NULL));
    }
    
    return GenericWindow::CreateNewWindow(Msg, hInstance, nCmdShow);
}

LRESULT CALLBACK MainWindow::WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CTLCOLORSTATIC: return WMCtlColorStatic(wParam);
        case WM_PAINT: WMPaint(thisWindow); break;
        case WM_LBUTTONUP: WMLeftMouseButtonUp(thisWindow, lParam); break;
        case WM_MOUSEMOVE: WMMouseMove(thisWindow); break;
        case WM_MOUSEHOVER: WMMouseHover(thisWindow, lParam); break;
        case WM_MOUSELEAVE: WMMouseLeave(thisWindow); break;
        case WM_TIMER: WMTimer(thisWindow); break;
        case WM_NCHITTEST: return NCHitTest(thisWindow, lParam);
        case WM_CLOSE: DestroyWindow(thisWindow); break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(thisWindow, message, wParam, lParam);
    }
    
    return 0;
}

LRESULT MainWindow::WMCtlColorStatic(WPARAM wParam)
{
    HDC hdc = (HDC) wParam;
    SetTextColor(hdc, RGB(255,255,255));
    SetBkMode(hdc, TRANSPARENT);
    return (LRESULT)GetStockObject(NULL_BRUSH);
}

void MainWindow::WMPaint(HWND thisWindow)
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
    hbm = CreateCompatibleBitmap(mainHDC, mainWindowWidth, mainWindowHeight);
    SelectObject(bufferHDC, hbm);
    
    RECT outerBackground;
    SetRect(&outerBackground, 0, 0, mainWindowWidth, mainWindowHeight);
    
    HBRUSH brush = CreateSolidBrush(RGB(35, 39, 42));
    FillRect(bufferHDC, &outerBackground, brush);
    
    Graphics graphics(bufferHDC);
    
    graphics.DrawImage(images[0], 2, 0, 100, 18);
    graphics.DrawImage(images[closeImage], mainWindowWidth-30, 0, 20, 20);
    graphics.DrawImage(images[minimizeImage], mainWindowWidth-70, 0, 20, 20);
    
    BitBlt(mainHDC, 0, 0, mainWindowWidth, mainWindowHeight, bufferHDC, 0, 0, SRCCOPY);
    
    DeleteObject(hbm);
    DeleteDC(bufferHDC);
    DeleteDC(mainHDC);

    DeleteObject(brush);
    EndPaint(thisWindow, &ps);
}

void MainWindow::WMLeftMouseButtonUp(HWND thisWindow, LPARAM lParam)
{
    POINT mousePoint;
    mousePoint.x = LOWORD(lParam);
    mousePoint.y = HIWORD(lParam);
    
    if(PtInRect(&closeButton, mousePoint))
    {
        PostMessage(thisWindow, WM_SYSCOMMAND, SC_CLOSE, 0);

    }
    else if(PtInRect(&minimizeButton, mousePoint))
    {
        PostMessage(thisWindow, WM_SYSCOMMAND, SC_MINIMIZE, 0);
    }
}

void MainWindow::WMMouseMove(HWND thisWindow)
{
    SetTimer(thisWindow, 10, 10, NULL);
    
    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(TRACKMOUSEEVENT);
    tme.dwFlags = TME_HOVER;
    tme.dwHoverTime = 10;
    tme.hwndTrack = thisWindow;
    TrackMouseEvent(&tme);
}

void MainWindow::WMMouseHover(HWND thisWindow, LPARAM lParam)
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
    
    if(buttonHover != currentButtonHover)
    {
        currentButtonHover = buttonHover;
        RedrawWindow(thisWindow, NULL, NULL, RDW_INVALIDATE);
    }
}

void MainWindow::WMMouseLeave(HWND thisWindow)
{
    if(buttonHover != 0)
    {
        buttonHover = 0;
        currentButtonHover = 0;
        RedrawWindow(thisWindow, NULL, NULL, RDW_INVALIDATE);
    }
}

void MainWindow::WMTimer(HWND thisWindow)
{
    KillTimer(thisWindow, 100);
    
    RECT windowRect;
    RECT closeRect;
    RECT minimizeRect;
    POINT mousePoint;
    
    GetCursorPos(&mousePoint);
    GetWindowRect(thisWindow,&windowRect);
    closeRect = windowRect;
    minimizeRect = windowRect;
    
    closeRect.left = closeRect.left + mainWindowWidth - 40;
    closeRect.bottom = closeRect.bottom - mainWindowHeight + 20;
    
    minimizeRect.left = minimizeRect.left + mainWindowWidth - 80;
    minimizeRect.right = minimizeRect.right  - 40;
    minimizeRect.bottom = minimizeRect.bottom - mainWindowHeight + 20;

    if(!PtInRect(&closeRect,mousePoint) && !PtInRect(&minimizeRect,mousePoint)) PostMessage(thisWindow, WM_MOUSELEAVE, 0, 0L);
}

LRESULT MainWindow::NCHitTest(HWND thisWindow, LPARAM lParam)
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

void MainWindow::CreateComponents()
{
    SetWindowSubclass(StatusPanel::Init(thisWindow, instance), (SUBCLASSPROC) StatusPanel::WindowProc, 0, 1);
    SetWindowSubclass(PlayersPanel::Init(thisWindow, instance), (SUBCLASSPROC) PlayersPanel::WindowProc, 0, 1);
    SetWindowSubclass(SwapPanel::Init(thisWindow, instance), (SUBCLASSPROC) SwapPanel::WindowProc, 0, 1);
    
    errorLabel = CreateChildLabel("", 10, 685, thisWindow, LBL_ERROR);
    
    MainWindow::mainWindow = thisWindow;
}

void MainWindow::DisplayError(string errorMessage)
{
    SetWindowText(errorLabel, errorMessage.c_str());
}