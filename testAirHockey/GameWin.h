//GameWin.h

#ifndef GAMEWIN_H
#define GAMEWIN_H

#include "baseWin.h"
#include <string>
#include "resource.h"
#include "AirHockeyGame.h"
#include "BackBuffer.h"
#include <windows.h>

class GameWin:public BaseWin
{

    public:
        void wmKeyDown(WPARAM wParam){};
        void wmCreate(HWND hwnd);
        void wmLButtonDown();
        void wmRButtonDown();
        void wmCommand(WPARAM wParam);
        void mainloop();
        void wmDestroy();
        //need to be implemented

        void CreateWin(LPCTSTR WindowName);
        GameWin();
        GameWin(HINSTANCE ghAppInst); // initial some data and set menu
        virtual ~GameWin();



    private:
        static LRESULT CALLBACK WinProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        HINSTANCE   mghAppInst;
        HDC         mghSpriteDC;
        BackBuffer*    mgBackBuffer;
        AirHockeyGame* mgAirHockey;


        const int gClientWidth;
        const int gClientHeight;

        const int gWindowWidth;
        const int gWindowHeight;

        POINT gClientCenter;

        __int64 lastTime;
        __int64 cntsPerSec;
        double timeScale;
        double timeElapsed;


};



#endif
