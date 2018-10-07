#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <string>
#include <fstream>
#include <windows.h>
#include <iostream>

using namespace std;

class ErrorHandler
{
    public:
        static void Init(HINSTANCE instance);
        static void WriteError(string errorMessage, bool fatalError);
        static bool CheckErrors();
        static void ClearErrors();
    private:
        static string path;
        static bool encErr;
};

#endif

