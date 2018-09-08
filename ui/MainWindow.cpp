#include "MainWindow.h"

int MainWindow::userState = 1;
int MainWindow::currentUserState = 0;
bool MainWindow::firstLoad = true;
vector<PlayerWindow> MainWindow::playerWindows;
vector<HWND> MainWindow::playerStatus;
vector<string> MainWindow::currentStatus {"offline", "offline", "offline", "offline"};
const string MainWindow::imagePath = "C:\\Users\\Urt\\Documents\\Projects\\ArcTeam\\ArcTeam\\resources\\images\\";
vector<string> MainWindow::usernames;
vector<Image*> MainWindow::images;
RECT MainWindow::background;

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
    
    vector<string> statuses = {"offline", "happy", "good", "sad", "fine"};
    
    for(int i = 0; i < statuses.size(); i++)
    {
        string filePath = statuses[i] + ".jpg";
        wstring wImagePath = wstring(filePath.begin(), filePath.end());
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
    if(LOWORD(wParam) == BTN_ZERO)
    {
        MainWindow::ChangeState(0, thisWindow);
    }
    else if(LOWORD(wParam) == BTN_ONE)
    {
        MainWindow::ChangeState(1, thisWindow);
    }
    else if(LOWORD(wParam) == BTN_TWO)
    {
        MainWindow::ChangeState(2, thisWindow);
    }
    else if(LOWORD(wParam) == BTN_THREE)
    {
        MainWindow::ChangeState(3, thisWindow);
    }
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
}

void MainWindow::WMPaint(HWND thisWindow, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC mainHDC = GetDC(thisWindow);
    mainHDC = BeginPaint(thisWindow, &ps);

    Graphics graphics(mainHDC);

    vector<HWND> playStat = MainWindow::playerStatus;
    vector<string> curStat = MainWindow::currentStatus;
    vector<string> buttonImages {"offline", "happy", "good", "sad", "fine"};
    
    for(int i = 0; i < playStat.size(); i++)
    {
        int fieldLen = GetWindowTextLength(playStat[i]) + 1;
        char* fieldValue = new char[fieldLen];
        GetWindowText(playStat[i], &fieldValue[0], 8192);
        
        if(fieldValue != curStat[i] || MainWindow::firstLoad)
        {
            Image* thumbnail;
            
            for(int j = 0; j < buttonImages.size(); j++)
            {
                if(buttonImages[j] == string(fieldValue))
                {
                    thumbnail = images[j];
                }
            }

            graphics.DrawImage(thumbnail, 20 + (i * 130), 40, 100, 133);
            
            MainWindow::currentStatus[i] = string(fieldValue);
        }
    }
    
    if(MainWindow::userState != MainWindow::currentUserState)
    {
        for(int i = 1; i < buttonImages.size(); i++)
        {
            if(i == MainWindow::userState || i == MainWindow::currentUserState || MainWindow::firstLoad)
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

                if(MainWindow::userState == i)
                {
                    brush = CreateSolidBrush(RGB(198, 0, 0));
                }

                SetRect(&bknd, xPos - 10, yPos - 10, xPos + 160, yPos + 210);
                FillRect(mainHDC, &bknd, brush);
                DeleteObject(brush);

                graphics.DrawImage(images[i], xPos, yPos, 150, 200);
            }
        }
        
        MainWindow::currentUserState = MainWindow::userState;
    }
    
    MainWindow::firstLoad = false;

    EndPaint(thisWindow, &ps);
    
    ReleaseDC(thisWindow,mainHDC);
}

void MainWindow::CreateComponents()
{
    for(int i = 0; i < usernames.size(); i++)
    {
        MainWindow::playerWindows.push_back(PlayerWindow(thisWindow, instance, usernames[i], LBL_ONE + i, 22 + (130 * i) + (2 * (14 - usernames[i].length())), 14));
        
        MainWindow::playerStatus.push_back(CreateWindow("static", "offline", WS_CHILD, 18 + (130 * i), 20, 100, 25, thisWindow, (HMENU)LBL_ONE + i + 8, instance, NULL));
    }
}

void MainWindow::SetUsernames(vector<string> newUsernames)
{
    usernames = newUsernames;
}

void MainWindow::SetPlayerStatus(string changeUsername, string statusName)
{
    vector<PlayerWindow> playerWindows = MainWindow::playerWindows;
    
    for(int i = 0; i < playerWindows.size(); i++)
    {
        if(playerWindows[i].GetUsername() == changeUsername)
        {
            playerWindows[i].SetStatus(statusName);
            break;
        }
    }
}

void MainWindow::ChangeState(int state, HWND thisWindow)
{
    WebHandler::PushStatus(state, UserHandler::GetUsername());
    userState = state;
    
    RedrawWindow(thisWindow, NULL, NULL, RDW_INVALIDATE);
}