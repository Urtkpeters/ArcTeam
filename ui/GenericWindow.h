#ifndef GENERICWINDOW_H
#define GENERICWINDOW_H

#include <string>
#include <windows.h>

#include "../resources.h"

using namespace std;

class GenericWindow
{
    public:
        MSG CreateNewWindow(MSG Msg, HINSTANCE hInstance, int nCmdShow);
    protected:
        HWND thisWindow;
        HINSTANCE instance;
        int cmdShow;
        WNDCLASSEX wc;
        string strClassName;
        string windowTitle;
        int windowWidth;
        int windowHeight;
        int windowStartX;
        int windowStartY;
        
        string GetInputField(HWND field);
        HWND CreateChildInput(int elementStartX, int elementStartY, int elementWidth, int elementHeight, HWND parentElement, int elementId);
        HWND CreateChildListbox(int elementStartX, int elementStartY, int elementWidth, int elementHeight, HWND parentElement, int elementId);
        HWND CreateChildLabel(string labelText, int elementStartX, int elementStartY, HWND parentElement, int elementId);
        void CreateChildButton(string labelText, int elementStartX, int elementStartY, int elementWidth, int elementHeight, HWND parentElement, int elementId);
        void CreateChildImageButton(int imageId, int elementStartX, int elementStartY, int elementWidth, int elementHeight, HWND parentElement, int elementId);
        MSG DisplayWindow(MSG Msg);
        
        virtual void CreateComponents(){};
        
        static const string applicationVersion;
        static const int IMG_TITLEBAR;
};

#endif