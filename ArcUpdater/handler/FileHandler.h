#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class FileHandler
{
    public:
        static void CheckDownloadDirectory();
        static void UnpackDownload();
        static string GetCurrentVersion();
        static string GetPreviousVersion();
        static vector<string> Split(const string& inputString, char delimiter);
        static string GetAppPath();
    private:
        static void CreateVersionFile();
        static vector<string> ReadVersionFile();
        static void DeleteDirectory(string filePath);
        static void MoveFiles(string destinationPath, string sourcePath);
};

#endif

