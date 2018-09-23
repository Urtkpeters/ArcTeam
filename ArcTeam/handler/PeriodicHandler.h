#ifndef PERIODICHANDLER_H
#define PERIODICHANDLER_H

#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>

#include "PlayerHandler.h"
#include "../ui/panel/PlayersPanel.h"

using namespace std;
using json = nlohmann::json;

class PeriodicHandler
{
    public:
        static void CreateThread();
        static void KillThread();
        static bool GetThreadStatus();
    private:
        static bool stopThread;
        static bool threadRunning;
        
        static void CheckStatus();
};

#endif