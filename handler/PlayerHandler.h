#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include <vector>
#include <string>

#include "Player/Player.h"
#include "../ui/MainWindow.h"
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
    private:
        static vector<Player> players;
        
        static const vector<string> statuses;
};

#endif

