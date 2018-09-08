#ifndef USERHANDLER_H
#define USERHANDLER_H

#include <string>
#include <vector>

using namespace std;

class UserHandler
{
    public:
        static void SetUsername(string newUsername);
        static string GetUsername();
        static vector<string> GetUsers();
    private:
        static string username;
        static const vector<string> users;
};

#endif

