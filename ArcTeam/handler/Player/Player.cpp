#include "Player.h"

Player::Player(string newUsername, vector<string> newStatuses)
{
    username = newUsername;
    statuses = newStatuses;
}

bool Player::SetStatus(int newStatusId)
{
    bool statusChanged = false;
    
    if(newStatusId != statusId)
    {
        statusId = newStatusId;
        
        status = statuses[statusId];
        
        statusChanged = true;
    }
    
    return statusChanged;
}

void Player::CreateLabel(HWND mainWindow, HINSTANCE hInstance, int labelId, int startX, int startY)
{
    label = CreateWindow("static", username.c_str(), WS_CHILD | WS_VISIBLE, startX, startY, 100, 25, mainWindow, (HMENU)labelId, hInstance, NULL);
}

string Player::GetUsername()
{
    return username;
}

string Player::GetStatus()
{
    return status;
}