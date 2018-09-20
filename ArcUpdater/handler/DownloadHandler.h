#ifndef DOWNLOADHANDLER_H
#define DOWNLOADHANDLER_H

#include <nlohmann/json.hpp>
#include <thread>
#include <vector>

#include "WebHandler.h"
#include "FileHandler.h"
#include "../ui/UpdaterWindow.h"

using namespace std;
using json = nlohmann::json;

class DownloadHandler
{
    public:
        static void Init();
    private:
        static void CheckVersion();
};

#endif

