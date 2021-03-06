#include "PlayerHandler.h"

vector<Player> PlayerHandler::players;
bool PlayerHandler::statusChange;

const vector<string> PlayerHandler::statuses = {"offline", "happy", "good", "sad", "fine"};

void PlayerHandler::Init()
{
    string username = UserHandler::GetUsername();
    vector<string> users = UserHandler::GetUsers();
    
    for(int i = 0; i < users.size(); i++)
    {
        // Check to make sure that the current looped username is not the logged in username
        if(users[i] != username)
        {
            // 100 used to be referenced to a global constant
            players.push_back(Player(users[i], statuses));
        }
    }
    
    statusChange = true;
}

vector<Player> PlayerHandler::GetPlayers()
{
    return players;
}

vector<string> PlayerHandler::GetUsernames()
{
    vector<string> usernames;
    vector<Player> players = PlayerHandler::GetPlayers();
    
    for(int i = 0; i < players.size(); i++)
    {
        usernames.push_back(players[i].GetUsername());
    }
    
    return usernames;
}

void PlayerHandler::SetPlayerStatus(string username, int newStatusId)
{
    for(int i = 0; i < players.size(); i++)
    {
        if(players[i].GetUsername() == username)
        {
            if(players[i].SetStatus(newStatusId))
            {
                statusChange = true;
            }
        }
    }
}

bool PlayerHandler::GetStatusChange()
{
    bool origValue = statusChange;
    
    statusChange = false;
    
    return origValue;
}

vector<string> PlayerHandler::GetStatuses()
{
    return statuses;
}