#include "Player.h"

Player::Player(string newUsername)
{
    username = newUsername;
    statusChanged = true;
}

void Player::SetStatus(int newStatusId)
{
    if(newStatusId != statusId)
    {
        statusId = newStatusId;
        
        switch(statusId)
        {
            case 0:
                status = "offline";
                break;
            case 1:
                status = "happy";
                break;
            case 2:
                status = "good";
                break;
            case 3:
                status = "sad";
                break;
            case 4:
                status = "fine";
                break;
        }
        
        statusChanged = true;
    }
    else
    {
        statusChanged = false;
    }
}

void Player::CreateLabel(HWND mainWindow, HINSTANCE hInstance, int labelId, int startX, int startY)
{
    label = CreateWindow("static", username.c_str(), WS_CHILD | WS_VISIBLE, startX, startY, 100, 25, mainWindow, (HMENU)labelId, hInstance, NULL);
}

bool Player::HasChange()
{
    return statusChanged;
}

string Player::GetUsername()
{
    return username;
}

string Player::GetStatus()
{
    return status;
}