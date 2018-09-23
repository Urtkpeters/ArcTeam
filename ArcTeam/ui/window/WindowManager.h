#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "UserWindow.h"
#include "MainWindow.h"
#include "../../handler/PeriodicHandler.h"
#include "../../handler/PlayerHandler.h"
#include "../../handler/WebHandler.h"
#include "../../handler/UserHandler.h"

class WindowManager
{
    public:
        static MSG CreateUI(MSG Msg, HINSTANCE hInstance, int nCmdShow);
        static string GetWindow();
        static void SetWindow(string newWindow);
    private:
        static string window;
};

#endif

