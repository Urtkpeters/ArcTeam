#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include <vector>
#include <string>

#include "Player/Player.h"
#include "../ui/window/MainWindow.h"
#include "UserHandler.h"

using namespace std;

class PlayerHandler
{
    public:
        static void Init();
        static vector<Player> GetPlayers();
        static vector<string> GetUsernames();
        static void SetPlayerStatus(string username, int newStatusId);
        static vector<string> GetStatuses();
        static bool GetStatusChange();
    private:
        static vector<Player> players;
        static bool statusChange;
        
        static const vector<string> statuses;
};

#endif

