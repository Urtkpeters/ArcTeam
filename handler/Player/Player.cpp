#include "Player.h"

Player::Player(string newUsername)
{
    username = newUsername;
}

string Player::GetUsername()
{
    return username;
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
    }
}

string Player::GetStatus()
{
    return status;
}

