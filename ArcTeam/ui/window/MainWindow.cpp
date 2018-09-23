#include "MainWindow.h"

vector<string> MainWindow::usernames;
RECT MainWindow::background;
HWND MainWindow::mainWindow;
HWND MainWindow::errorLabel;
HWND MainWindow::titleLabel;
vector<Image*> MainWindow::images;

const vector<string> MainWindow::imageNames {"close", "close_hover"};
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
    
    SetRect(&background, 0, 0, mainWindowWidth, mainWindowHeight);
    
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(instance, szPath, MAX_PATH);
    string basePath = string(szPath);
    
    for(int i = 0; i < imageNames.size(); i++)
    {
        string path = basePath.substr(0, basePath.length() - 11) + "resources\\images\\" + imageNames[i] + ".png";
        
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        
        Image image(wcImagePath);
        
        image.GetThumbnailImage(20, 20, NULL, NULL);
        images.push_back(image.GetThumbnailImage(20, 20, NULL, NULL));
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
    
    mainHDC = BeginPaint(thisWindow, &ps);
    bufferHDC = CreateCompatibleDC(mainHDC);
    hbm = CreateCompatibleBitmap(mainHDC, mainWindowWidth, mainWindowHeight);
    SelectObject(bufferHDC, hbm);
    
    RECT outerBackground;
    SetRect(&outerBackground, 0, 0, mainWindowWidth, mainWindowHeight);
    
    HBRUSH brush = CreateSolidBrush(RGB(35, 39, 42));
    FillRect(bufferHDC, &outerBackground, brush);
    
    Graphics graphics(bufferHDC);
    
    graphics.DrawImage(images[0], mainWindowWidth-20, 0, 20, 20);
    
    BitBlt(mainHDC, 0, 0, mainWindowWidth, mainWindowHeight, bufferHDC, 0, 0, SRCCOPY);
    
    DeleteObject(hbm);
    DeleteDC(bufferHDC);
    DeleteDC(mainHDC);

    DeleteObject(brush);
    EndPaint(thisWindow, &ps);
}

void MainWindow::WMLeftMouseButtonUp(HWND thisWindow, LPARAM lParam)
{
    int mPosX = LOWORD(lParam);
    int mPosY = HIWORD(lParam);
    
    if(mPosX > mainWindowWidth - 20 && mPosY < 20)
    {
        PostMessage(thisWindow, WM_CLOSE, 0, 0);
    }
}

LRESULT MainWindow::NCHitTest(HWND thisWindow, LPARAM lParam)
{
    LRESULT hit = HTCLIENT;
    POINT point;

    point.x = LOWORD(lParam);
    point.y = HIWORD(lParam);

    ScreenToClient(thisWindow, &point);

    if(point.x < 500 && point.y < 20)
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
    
    titleLabel = CreateChildLabel("ArcTeam v" + applicationVersion, 5, 3, thisWindow, LBL_TITLE);
    errorLabel = CreateChildLabel("", 10, 685, thisWindow, LBL_ERROR);
    
    MainWindow::mainWindow = thisWindow;
}

void MainWindow::SetUsernames(vector<string> newUsernames)
{
    usernames = newUsernames;
}

void MainWindow::RefreshWindow()
{
    RedrawWindow(MainWindow::mainWindow, NULL, NULL, RDW_INVALIDATE);
}

void MainWindow::DisplayError(string errorMessage)
{
    SetWindowText(errorLabel, errorMessage.c_str());
}