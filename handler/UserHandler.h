#ifndef USERHANDLER_H
#define USERHANDLER_H

#include <string>
#include <vector>

#include "WebHandler.h"

using namespace std;

class UserHandler
{
    public:
        static void SetUsername(string newUsername);
        static void SetState(int newState);
        static string GetUsername();
        static int GetState();
        static int GetLastState();
        static bool GetStateChange();
        static vector<string> GetUsers();
    private:
        static string username;
        static int state;
        static int lastState;
        static bool stateChange;
        
        static const vector<string> users;
};

#endif

