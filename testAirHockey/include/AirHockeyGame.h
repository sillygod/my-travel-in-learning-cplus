//AirHockeyGame.h

#ifndef AIRHOCKEYGAME_H
#define AIRHOCKEYGAME_H

#include <windows.h>
#include "Circle.h"
#include "Rect.h"
#include "Sprite.h"


class AirHockeyGame
{

    public:
        AirHockeyGame(HINSTANCE hAppInst, HWND hMainWnd, Vec2 wndCenterPt);
        ~AirHockeyGame();
        void pause();
        void unpause();

        void update(float dt);
        void draw(HDC hBackBufferDC, HDC hSpriteDC);


    private:
        void updateBluePaddle(float dt);
        void updateRedPaddle(float dt);
        void updatePuck(float dt);

        bool paddlePuckCollision(Sprite* paddle);
        void increaseScore(bool blue);




        HINSTANCE mhAppInst;
        HWND      mhMainWnd;
        Vec2      mWndCenterPt;

        int mBlueScore;
        int mRedScore;

        bool mPaused;

        const float MAX_PUCK_SPEED;
        const float RED_SPEED;

        float mRedRecoverTime;

        Sprite* mGameBoard;
        Sprite* mBluePaddle;
        Sprite* mRedPaddle;
        Sprite* mPuck;

        POINT mLastMousePos;
        POINT mCurrMousePos;

        Rect mBlueBounds;
        Rect mRedBounds;
        Rect mBoardBounds;
        Rect mBlueGoal;
        Rect mRedGoal;


};


#endif //AIRHOCKEYGAME_H
