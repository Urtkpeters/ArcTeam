#include "PeriodicHandler.h"

bool PeriodicHandler::stopThread = false;

void PeriodicHandler::CreateThread()
{
    thread periodicThread(CheckStatus);
    periodicThread.detach();
}

void PeriodicHandler::KillThread()
{
    stopThread = true;
}

void PeriodicHandler::CheckStatus()
{
    json jsonResponse = WebHandler::GetStatus();
    
    vector<Player> players = PlayerHandler::GetPlayers();
    
    for(int i = 0; i < players.size(); i++)
    {
        string newStatus = jsonResponse["aryStatus"][players[i].GetUsername()];
        
        players[i].SetStatus(stoi(newStatus));
        PlayerHandler::SetPlayerStatus(players[i].GetUsername(), stoi(newStatus));
    }
    
    // This should be made a setting
    this_thread::sleep_for(chrono::milliseconds(5000));
    
    if(!stopThread)
    {
        CheckStatus();
    }
}