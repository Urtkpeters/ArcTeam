#include "MainWindow.h"

vector<string> MainWindow::usernames;
vector<Image*> MainWindow::images;
RECT MainWindow::background;
HWND MainWindow::mainWindow;
HWND MainWindow::errorLabel;
HWND MainWindow::titleLabel;

MSG MainWindow::CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow)
{
    wc.lpfnWndProc = WindowProc;
    strClassName = "mainWindow";
    windowTitle = "ArcTeam v" + applicationVersion;
    windowStartX = 100;
    windowStartY = 100;
    windowWidth = 750;
    windowHeight = 750;
    
    SetRect(&background, 0, 0, 550, 750);
    
    vector<string> statuses = PlayerHandler::GetStatuses();
    
    for(int i = 0; i < statuses.size(); i++)
    {
        TCHAR szPath[MAX_PATH];
        GetModuleFileName(hInstance, szPath, MAX_PATH);
        
        string path = string(szPath);
        path = path.substr(0, path.length() - 11) + "resources\\images\\" + statuses[i] + ".jpg";
        
        wstring wImagePath = wstring(path.begin(), path.end());
        const wchar_t* wcImagePath = wImagePath.c_str();
        Image image(wcImagePath);
        
        images.push_back(image.GetThumbnailImage(715, 953, NULL, NULL));
    }
    
    return GenericWindow::CreateNewWindow(Msg, hInstance, nCmdShow);
}

LRESULT CALLBACK MainWindow::WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    
    switch(message)
    {
        case WM_ERASEBKGND: return true;
        case WM_CTLCOLORSTATIC: return WMCtlColorStatic(thisWindow, wParam, lParam, hdc);
        case WM_LBUTTONUP: WMLeftMouseButtonUp(thisWindow, wParam, lParam); break;
        case WM_PAINT: WMPaint(thisWindow, wParam, lParam); break;
        case WM_CLOSE: DestroyWindow(thisWindow); break;
        case WM_DESTROY: PostQuitMessage(0); break;
        case WM_NCHITTEST: return NCHitTest(thisWindow, wParam, lParam);
        default: return DefWindowProc(thisWindow, message, wParam, lParam);
    }
    
    return 0;
}

void MainWindow::WMLeftMouseButtonUp(HWND thisWindow, WPARAM wParam, LPARAM lParam)
{
    int mPosX = LOWORD(lParam);
    int mPosY = HIWORD(lParam);
    
    if(mPosX > 500 && mPosY < 20)
    {
        PostMessage(thisWindow, WM_CLOSE, 0, 0);
    }
    
    if(mPosX > 90 && mPosX < 240)
    {
        // Happy
        if(mPosY > 210 && mPosY < 410)
        {
            MainWindow::ChangeState(1, thisWindow);
        }
        
        // Sad
        if(mPosY > 450 && mPosY < 650)
        {
            MainWindow::ChangeState(3, thisWindow);
        }
    }
    
    if(mPosX > 290 && mPosX < 440)
    {
        // Good
        if(mPosY > 210 && mPosY < 410)
        {
            MainWindow::ChangeState(2, thisWindow);
        }
        
        // Fine
        if(mPosY > 450 && mPosY < 650)
        {
            MainWindow::ChangeState(4, thisWindow);
        }
    }
    
//    if(mPosX > 0 && mPosX < 100 && mPosY > 0 && mPosY < 100)
//    {
//        ErrorHandler::WriteError("this is error");
//    }
}

void MainWindow::WMPaint(HWND thisWindow, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC mainHDC;
    HDC bufferHDC;
    HBITMAP hbm;
    
    mainHDC = BeginPaint(thisWindow, &ps);
    bufferHDC = CreateCompatibleDC(mainHDC);
    hbm = CreateCompatibleBitmap(mainHDC, 750, 750);
    SelectObject(bufferHDC, hbm);
    
    RECT outerBackground;
    SetRect(&outerBackground, 0, 0, 750, 750);
    
    HBRUSH brush = CreateSolidBrush(RGB(72, 79, 91));
    FillRect(bufferHDC, &outerBackground, brush);

    Graphics graphics(bufferHDC);

    vector<string> statuses = PlayerHandler::GetStatuses();
    
    if(UserHandler::GetStateChange())
    {
        for(int i = 1; i < statuses.size(); i++)
        {
//            int state = UserHandler::GetState();
//            int lastState = UserHandler::GetLastState();
//            
//            if(i == state || i == lastState || lastState == 0)
//            {
//                RECT bknd;
//                brush = CreateSolidBrush(RGB(240, 240, 240));
//
//                if(state == i)
//                {
//                    brush = CreateSolidBrush(RGB(198, 0, 0));
//                }
//
//                SetRect(&bknd, xPos - 10, yPos - 10, xPos + 160, yPos + 210);
//                FillRect(mainHDC, &bknd, brush);
//                DeleteObject(brush);
//
                graphics.DrawImage(images[i], 10, 30 + ((i - 1) * 120), 80, 107);
//            }
        }
    }
    
    BitBlt(mainHDC, 0, 0, 750, 750, bufferHDC, 0, 0, SRCCOPY);
    DeleteObject(hbm);
    DeleteDC(bufferHDC);
    DeleteDC(mainHDC);

    DeleteObject(brush);
    EndPaint(thisWindow, &ps);
}

LRESULT MainWindow::WMCtlColorStatic(HWND thisWindow, WPARAM wParam, LPARAM lParam, HDC hdc)
{
    hdc = (HDC) wParam;
    SetTextColor(hdc, RGB(255,255,255));
    SetBkMode(hdc, TRANSPARENT);
    return (LRESULT)GetStockObject(NULL_BRUSH);
}

LRESULT MainWindow::NCHitTest(HWND thisWindow, WPARAM wParam, LPARAM lParam)
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
    SetWindowSubclass(PlayersPanel::Init(thisWindow, instance, images), (SUBCLASSPROC) PlayersPanel::WindowProc, 0, 1);
    SetWindowSubclass(SwapPanel::Init(thisWindow, instance), (SUBCLASSPROC) SwapPanel::WindowProc, 0, 1);
    SetWindowSubclass(FooterPanel::Init(thisWindow, instance), (SUBCLASSPROC) FooterPanel::WindowProc, 0, 1);
    
    vector<Player> players = PlayerHandler::GetPlayers();
    
    for(int i = 0; i < players.size(); i++)
    {
        int xPos = 150;
        int yPos = 14;
        
        if(i == 1 || i == 3) xPos = 600;
        if(i == 2 || i == 3) yPos = 540;
        
        players[i].CreateLabel(thisWindow, instance, LBL_ONE + i, xPos, yPos);
    }
    
    titleLabel = CreateChildLabel("ArcTeam v" + applicationVersion, 5, 3, thisWindow, LBL_TITLE);
    errorLabel = CreateChildLabel("", 10, 685, thisWindow, LBL_ERROR);
    
    MainWindow::mainWindow = thisWindow;
}

void MainWindow::SetUsernames(vector<string> newUsernames)
{
    usernames = newUsernames;
}

void MainWindow::ChangeState(int state, HWND thisWindow)
{
    UserHandler::SetState(state);
    
    if(UserHandler::GetStateChange())
    {
        RedrawWindow(thisWindow, NULL, NULL, RDW_INVALIDATE);
    }
}

void MainWindow::RefreshWindow()
{
    RedrawWindow(MainWindow::mainWindow, NULL, NULL, RDW_INVALIDATE);
}

void MainWindow::DisplayError(string errorMessage)
{
    SetWindowText(errorLabel, errorMessage.c_str());
}