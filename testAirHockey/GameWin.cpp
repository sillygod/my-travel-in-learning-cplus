//GameWin.cpp

#include "GameWin.h"

GameWin::GameWin(HINSTANCE ghAppInst)
:gClientWidth(864),gClientHeight(504),gWindowWidth(gClientWidth+6),gWindowHeight(gClientHeight+52)
{

    mghAppInst=ghAppInst;
    mghSpriteDC=0;
    mgBackBuffer=0;
    mgAirHockey=0;


    setMenu(mghAppInst,IDR_MENU1);

    gClientCenter.x=gClientWidth/2;
    gClientCenter.y=gClientHeight/2;

    lastTime = 0;
    cntsPerSec = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
    timeScale = 1.0 / (double)cntsPerSec;
    timeElapsed = 0.0f;

    regWindow(ghAppInst,"test",WinProc);

}


GameWin::GameWin()
:gClientWidth(0),gClientHeight(0),gWindowWidth(0),gWindowHeight(0)
{
    mghAppInst=0;
    mghSpriteDC=0;
    mgBackBuffer=0;
    mgAirHockey=0;
    lastTime=0;
    cntsPerSec=0;
    timeScale=0.0f;
    timeElapsed=0.0f;

    gClientCenter.x=0;
    gClientCenter.y=0;

}



void GameWin::CreateWin(LPCTSTR WindowName)
{
    createWindow(mghAppInst,WindowName,gWindowWidth,gWindowHeight);
}

GameWin::~GameWin()
{
    if(mghSpriteDC!=0 && mgBackBuffer!=0 && mgAirHockey!=0)
    {
        DeleteObject(mghSpriteDC);
        delete mgBackBuffer;
        delete mgAirHockey;
    }
}

LRESULT CALLBACK GameWin::WinProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    GameWin bee;

    return bee.ImpleWinProc(hwnd,Msg,wParam,lParam);
}


void GameWin::wmCreate(HWND hwnd)
{
    // Create the hockey game.
		mgAirHockey = new AirHockeyGame(mghAppInst, hwnd, gClientCenter);

		// Create system memory DCs
		mghSpriteDC = CreateCompatibleDC(0);

		// Create the backbuffer.
		mgBackBuffer = new BackBuffer(hwnd, gClientWidth, gClientHeight);

}


void GameWin::wmCommand(WPARAM wParam)
{

    switch(LOWORD(wParam))
    {

        case IDM_EXIT1:
			DestroyWindow(mHwnd);
			break;
    }

}

void GameWin::wmLButtonDown()
{
    mgAirHockey->unpause();
}

void GameWin::wmRButtonDown()
{
    mgAirHockey->pause();
}

void GameWin::wmDestroy()
{

    PostQuitMessage(0);
}

void GameWin::mainloop()
{

    // Get the time now.
    __int64 currTime = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

    // Compute the differences in time from the last
    // time we checked.  Since the last time we checked
    // was the previous loop iteration, this difference
    // gives us the time between loop iterations...
    // or, I.e., the time between frames.
    double deltaTime = (double)(currTime - lastTime) * timeScale;

    timeElapsed += deltaTime;

    // Only update once every 1/100 seconds.
    if( timeElapsed >= 0.01 )
    {
        // Update the game and draw everything.
        mgAirHockey->update((float)timeElapsed);

        // Draw every frame.
        mgAirHockey->draw(mgBackBuffer->getDC(), mghSpriteDC);

       // Now present the backbuffer contents to the main
        // window client area.
        mgBackBuffer->present();

        timeElapsed = 0.0;
    }

    // We are at the end of the loop iteration, so
    // prepare for the next loop iteration by making
    // the "current time" the "last time."
    lastTime = currTime;


}
