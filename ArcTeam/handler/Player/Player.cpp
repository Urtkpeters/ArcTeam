#include "Player.h"

Player::Player(string newUsername, vector<string> newStatuses)
{
    username = newUsername;
    statusChanged = true;
    statuses = newStatuses;
}

void Player::SetStatus(int newStatusId)
{
    if(newStatusId != statusId)
    {
        statusId = newStatusId;
        
        status = statuses[statusId];
        
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