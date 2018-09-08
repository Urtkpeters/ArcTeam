#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <string>

using namespace std;

class Player
{
    public:
        Player(string newUsername);
        void SetStatus(int newStatusId);
        string GetUsername();
        string GetStatus();
    private:
        HWND label;
        int statusId;
        string username;
        string status = "offline";
};

#endif

