// giAirHockey.cpp
// By sillygod
// August 24, 2004.
//
//=========================================================
// Includes
//=========================================================
#include "main.h"
#include "AirHockeyGame.h"
#include "BackBuffer.h"
#include "CTimer.h"
#include "Win.h"
using namespace std;

//=========================================================
// Globals
//=========================================================
HWND        ghMainWnd  = 0;
HDC         ghSpriteDC = 0;

BackBuffer*    gBackBuffer = 0;
AirHockeyGame* gAirHockey  = 0;

string gWndCaption = "paddle game";
void DrawFramesPerSecond(float deltaTime);

// Client dimensions exactly equal dimensions of
// background bitmap.  This is found by inspecting
// the bitmap in an image editor, for example.
const int gClientWidth  = 864;
const int gClientHeight = 504;

// Center point of client rectangle.
const POINT gClientCenter =
{
	gClientWidth  / 2,
	gClientHeight / 2
};

// Pad window dimensions so that there is room for window
// borders, caption bar, and menu.
const int gWindowWidth  = gClientWidth  + 6;
const int gWindowHeight = gClientHeight + 52;



class gameEngine : public Wnd
{
public:
    gameEngine(){};

    ~gameEngine(){
        this->shutDown();
    };

    bool init();

    WPARAM start();

    WPARAM Run();

    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void shutDown();


private:
    CTimer *mTimer;


};

bool gameEngine::init(){
// initial the window, register, create, show

    this->setMenu(MAKEINTRESOURCE(IDR_MENU1));
    //set menu before register window
    if(this->Register() && this->Create(gWindowWidth, gWindowHeight)){
        return true;
    }
    else{
        return false;
    }

}


void gameEngine::shutDown(){
    delete mTimer;
}


WPARAM gameEngine::start(){
    mTimer = new CTimer();
    return this->Run();
}


WPARAM gameEngine::Run(){

    MSG msg; //must initialize first

	ZeroMemory(&msg, sizeof(MSG));

	while(msg.message!=WM_QUIT)
	{

		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage( &msg );
			DispatchMessage ( &msg );
		}
		else
		{
			// tick fps to 60
			mTimer->Tick(60.0);
			gAirHockey->update(mTimer->GetTimeElapsed());

            // Draw every frame.
            gAirHockey->draw(gBackBuffer->getDC(), ghSpriteDC);

            DrawFramesPerSecond(mTimer->GetTimeElapsed());

            // Now present the backbuffer contents to the main
            // window client area.
            gBackBuffer->present();

		}
	}

	return msg.wParam;
}

LRESULT CALLBACK gameEngine::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

    switch( uMsg )
	{
	// Create application resources.
	case WM_CREATE:

		// Create the hockey game.
		gAirHockey = new AirHockeyGame(
			this->gethInstance(), hWnd, gClientCenter);

		// Create system memory DCs
		ghSpriteDC = CreateCompatibleDC(0);

		// Create the backbuffer.
		gBackBuffer = new BackBuffer(
			hWnd,
			gClientWidth,
			gClientHeight);

		return 0;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		// Destroy the window when the user selects the 'exit'
		// menu item.
		case IDM_EXIT1:
			DestroyWindow(ghMainWnd);
			break;

		}
		return 0;

	// Left mouse button to unpause the game.
	case WM_LBUTTONDOWN:
		gAirHockey->unpause();
		return 0;

	// Right mouse button to pause the game.
	case WM_RBUTTONDOWN:
		gAirHockey->pause();
		return 0;

	// Destroy application resources.
	case WM_DESTROY:
		delete gAirHockey;
		delete gBackBuffer;
		DeleteDC(ghSpriteDC);
		PostQuitMessage(0);
		return 0;
	}
	// Forward any other messages we didn't handle to the
	// default window procedure.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//=========================================================
// Name: WinMain
// Desc: Program execution starts here.
//=========================================================

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		PSTR cmdLine, int showCmd)
{
    gameEngine *engine = new gameEngine();

	if( engine->init()){
        ghMainWnd = engine->getHwnd();
	}

    return engine->start();
}



//=========================================================
// Name: DrawFramesPerSecond
// Desc: This function is called every frame and updates
//       the frame per second display in the main window
//       caption.
//=========================================================
void DrawFramesPerSecond(float deltaTime)
{
	// Make static so the variables persist even after
	// the function returns.
	static int   frameCnt    = 0;
	static float timeElapsed = 0.0f;
	static char  buffer[256];

	// Function called implies a new frame, so increment
	// the frame count.
	++frameCnt;

	// Also increment how much time has passed since the
	// last frame.
	timeElapsed += deltaTime;

	// Has one second passed?
	if( timeElapsed >= 1.0f )
	{
		// Yes, so compute the frames per second.
		// FPS = frameCnt / timeElapsed, but since we
		// compute only when timeElapsed = 1.0, we can
		// reduce to:
		// FPS = frameCnt / 1.0 = frameCnt.

		sprintf(buffer, "--Frames Per Second = %d", frameCnt);

		// Add the frames per second string to the main
		// window caption--that is, we'll display the frames
		// per second in the window's caption bar.
		string newCaption = gWndCaption + buffer;

		// Now set the new caption to the main window.
		SetWindowText(ghMainWnd, newCaption.c_str());
		// Reset the counters to prepare for the next time
		// we compute the frames per second.
		frameCnt    = 0;
		timeElapsed = 0.0f;
	}
}
