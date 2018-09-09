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
        void CreateLabel(HWND mainWindow, HINSTANCE hInstance, int labelId, int startX, int startY);
        bool HasChange();
        string GetUsername();
        string GetStatus();
    private:
        HWND label;
        int statusId;
        bool statusChanged;
        string username;
        string status = "offline";
};

#endif

