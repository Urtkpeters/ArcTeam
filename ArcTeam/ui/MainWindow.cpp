#include "MainWindow.h"

vector<string> MainWindow::usernames;
vector<Image*> MainWindow::images;
RECT MainWindow::background;
HWND MainWindow::mainWindow;
HWND MainWindow::errorLabel;

MSG MainWindow::CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow)
{
    wc.lpfnWndProc = WindowProc;
    strClassName = "mainWindow";
    windowTitle = "ArcTeam v" + applicationVersion;
    windowStartX = 100;
    windowStartY = 100;
    windowWidth = 550;
    windowHeight = 750;
    
    SetRect(&background, 0, 0, 550, 750);
    
    vector<string> statuses = PlayerHandler::GetStatuses();
    
    for(int i = 0; i < statuses.size(); i++)
    {
        TCHAR szPath[MAX_PATH];
        GetModuleFileName( hInstance, szPath, MAX_PATH);
        
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
    switch(message)
    {
        case WM_COMMAND: WMCommand(thisWindow, wParam, lParam); break;
        case WM_LBUTTONUP: WMLeftMouseButtonUp(thisWindow, wParam, lParam); break;
        case WM_PAINT: WMPaint(thisWindow, wParam, lParam); break;
        case WM_CLOSE: DestroyWindow(thisWindow); break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(thisWindow, message, wParam, lParam);
    }
    
    return 0;
}

void MainWindow::WMCommand(HWND thisWindow, WPARAM wParam, LPARAM lParam)
{
//    if(LOWORD(wParam) == BTN_ZERO)
//    {
//        MainWindow::ChangeState(0, thisWindow);
//    }
}

void MainWindow::WMLeftMouseButtonUp(HWND thisWindow, WPARAM wParam, LPARAM lParam)
{
    int mPosX = LOWORD(lParam);
    int mPosY = HIWORD(lParam);
    
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
    HDC mainHDC = GetDC(thisWindow);
    mainHDC = BeginPaint(thisWindow, &ps);

    Graphics graphics(mainHDC);

    vector<Player> players = PlayerHandler::GetPlayers();
    vector<string> statuses = PlayerHandler::GetStatuses();
    
    for(int i = 0; i < players.size(); i++)
    {
        string newStatus = players[i].GetStatus();
        
        if(players[i].HasChange())
        {
            Image* thumbnail;
            
            for(int j = 0; j < statuses.size(); j++)
            {
                if(statuses[j] == newStatus)
                {
                    thumbnail = images[j];
                }
            }

            graphics.DrawImage(thumbnail, 20 + (i * 130), 40, 100, 133);
        }
    }
    
    if(UserHandler::GetStateChange())
    {
        for(int i = 1; i < statuses.size(); i++)
        {
            int state = UserHandler::GetState();
            int lastState = UserHandler::GetLastState();
            
            if(i == state || i == lastState || lastState == 0)
            {
                int xPos = 90;
                int yPos = 210;

                if(i == 2 || i == 4)
                {
                    xPos += 200;
                }

                if(i == 3 || i == 4)
                {
                    yPos += 240;
                }

                RECT bknd;
                HBRUSH brush = CreateSolidBrush(RGB(240, 240, 240));

                if(state == i)
                {
                    brush = CreateSolidBrush(RGB(198, 0, 0));
                }

                SetRect(&bknd, xPos - 10, yPos - 10, xPos + 160, yPos + 210);
                FillRect(mainHDC, &bknd, brush);
                DeleteObject(brush);

                graphics.DrawImage(images[i], xPos, yPos, 150, 200);
            }
        }
    }

    EndPaint(thisWindow, &ps);
    
    ReleaseDC(thisWindow,mainHDC);
}

void MainWindow::CreateComponents()
{
    vector<Player> players = PlayerHandler::GetPlayers();
    
    for(int i = 0; i < players.size(); i++)
    {
        players[i].CreateLabel(thisWindow, instance, LBL_ONE + i, 22 + (130 * i) + (2 * (14 - players[i].GetUsername().length())), 14);
    }
    
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