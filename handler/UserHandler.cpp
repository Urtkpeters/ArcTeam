#include "UserHandler.h"

string UserHandler::username;
const vector<string> UserHandler::users {"[ARC]Odonen", "the[ARC]hitect", "[ARC]haedious", "An[ARC]hy", "[ARC]Nnemis"};

void UserHandler::SetUsername(string newUsername)
{
    username = newUsername;
}

string UserHandler::GetUsername()
{
    return username;
}

vector<string> UserHandler::GetUsers()
{
    return users;
}