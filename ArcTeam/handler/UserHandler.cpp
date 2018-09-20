#include "UserHandler.h"

string UserHandler::username;
int UserHandler::state = 1;
int UserHandler::lastState = 0;
bool UserHandler::stateChange = true;
const vector<string> UserHandler::users {"[ARC]Odonen", "the[ARC]hitect", "[ARC]haedious", "An[ARC]hy", "[ARC]Nnemis"};

void UserHandler::SetState(int newState)
{
    if(state != newState)
    {
        lastState = state;
        state = newState;
        stateChange = true;
        
        WebHandler::PushStatus(state, username);
    }
}

void UserHandler::SetUsername(string newUsername)
{
    username = newUsername;
}

string UserHandler::GetUsername()
{
    return username;
}

int UserHandler::GetState()
{
    stateChange = false;
    
    return state;
}

int UserHandler::GetLastState()
{
    return lastState;
}

bool UserHandler::GetStateChange()
{
    return stateChange;
}

vector<string> UserHandler::GetUsers()
{
    return users;
}