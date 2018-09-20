#include "PeriodicHandler.h"

bool PeriodicHandler::stopThread = false;
bool PeriodicHandler::threadRunning = false;

void PeriodicHandler::CreateThread()
{
    thread periodicThread(CheckStatus);
    threadRunning = true;
    periodicThread.detach();
}

void PeriodicHandler::KillThread()
{
    stopThread = true;
}

bool PeriodicHandler::GetThreadStatus()
{
    return threadRunning;
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
    else
    {
        threadRunning = false;
    }
}