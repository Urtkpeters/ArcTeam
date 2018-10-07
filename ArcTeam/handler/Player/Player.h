#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Player
{
    public:
        Player(string newUsername, vector<string> newStatuses);
        bool SetStatus(int newStatusId);
        void CreateLabel(HWND mainWindow, HINSTANCE hInstance, int labelId, int startX, int startY);
        string GetUsername();
        string GetStatus();
    private:
        HWND label;
        int statusId;
        string username;
        string status = "offline";
        vector<string> statuses;
};

#endif

