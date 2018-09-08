#include "UserWindow.h"
#include "WindowManager.h"

HWND UserWindow::label;
bool UserWindow::isRed = false;

MSG UserWindow::CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow)
{
    wc.lpfnWndProc = WindowProc;
    strClassName = "userWindow";
    windowTitle = "ArcTeam v" + applicationVersion;
    windowStartX = 100;
    windowStartY = 100;
    windowWidth = 400;
    windowHeight = 300;
    
    return GenericWindow::CreateNewWindow(Msg, hInstance, nCmdShow);
}

LRESULT CALLBACK UserWindow::WindowProc(HWND thisWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetWindowDC(label);
    
    switch(message)
    {
        case WM_CTLCOLOREDIT:
            if(isRed)
            {
                SetTextColor(hdc, RGB(198,0,0));
                return (LRESULT) CreateSolidBrush(RGB(198, 0, 0));
            }
            return false;
        case WM_COMMAND: WMCommand(thisWindow, wParam, lParam); break;
        case WM_CLOSE: DestroyWindow(thisWindow); break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(thisWindow, message, wParam, lParam);
    }
    
    return 0;
}

void UserWindow::WMCommand(HWND thisWindow, WPARAM wParam, LPARAM lParam)
{
    if(LOWORD(wParam) == BTN_USR)
    {
        if(UserHandler::GetUsername() == "")
        {
            isRed = true;
            RedrawWindow(thisWindow, NULL, NULL, RDW_INVALIDATE);
        }
        else
        {
            WindowManager::SetWindow("mainWindow");
            DestroyWindow(thisWindow);
        }
    }
    else if(HIWORD(wParam) == CBN_SELCHANGE)
    {
        int itemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
        TCHAR listItem[256];
        (TCHAR) SendMessage((HWND) lParam, (UINT) CB_GETLBTEXT, (WPARAM) itemIndex, (LPARAM) listItem);
        
        UserHandler::SetUsername(string(listItem));
    }
}

void UserWindow::CreateComponents()
{
    label = CreateChildLabel("Choose User", 145, 75, thisWindow, LBL_USR);
    
    HWND comboBox = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", "blep", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 115, 100, 140, 150, thisWindow, (HMENU) BTN_DPD, NULL, NULL);
    
    HWND cboOptions;
    cboOptions = GetDlgItem(thisWindow, IDD_OPTIONS_CBO);
    
    vector<string> users = UserHandler::GetUsers();    
    
    for(int i = 0; i < users.size(); i++)
    {
        SendMessage(comboBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)users[i].c_str()));
    }
    
    CreateChildButton("Submit", 150, 150, 70, 30, thisWindow, BTN_USR);
}