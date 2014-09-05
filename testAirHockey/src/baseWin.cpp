#include "baseWin.h"

BaseWin::BaseWin()
{
    mHwnd=0;
    mMenu=0;
}

void BaseWin::setMenu(HINSTANCE hInst,int menuID)
{
    LoadMenu(hInst, MAKEINTRESOURCE(menuID));
}


void BaseWin::regWindow(HINSTANCE hInst, LPCTSTR className,WNDPROC WinProc)
{

    mWndClsEx.cbSize        = sizeof(WNDCLASSEX);
    mWndClsEx.hInstance     = hInst;
    mWndClsEx.lpfnWndProc   = WinProc;
    mWndClsEx.cbClsExtra    = 0;
    mWndClsEx.cbWndExtra    = 0;
    mWndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    mWndClsEx.hCursor       = LoadCursor(NULL,IDC_ARROW);
    mWndClsEx.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
    mWndClsEx.style         = CS_HREDRAW | CS_VREDRAW;
    mWndClsEx.lpszClassName = className;
    mWndClsEx.hIconSm       = LoadIcon(NULL,IDI_APPLICATION);
    mWndClsEx.lpszMenuName  = NULL;


    RegisterClassEx(&mWndClsEx);

}




void BaseWin::createWindow(HINSTANCE hInst ,LPCTSTR WindowName, int width, int height)
{

    mHwnd=CreateWindowEx
          (
            WS_EX_OVERLAPPEDWINDOW,
            mWndClsEx.lpszClassName,
            WindowName,
            WS_OVERLAPPED | WS_SYSMENU,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            width,
            height,
            NULL,
            mMenu,
            hInst,
            NULL
          );

    if(!mHwnd)
        MessageBox(0,"window create error","error",MB_OK);


}



void BaseWin::showWindow(int cmdShow)
{
    ::ShowWindow(mHwnd,cmdShow);
    ::UpdateWindow(mHwnd);

}


WPARAM BaseWin::run()
{

    MSG msg;

    while(msg.message!=WM_QUIT)
    {

        if(PeekMessage(&msg,0,0,0,PM_REMOVE))
        {
            /* Translate virtual-key messages into character messages */
            TranslateMessage(&msg);
            /* Send message to WindowProcedure */
            DispatchMessage(&msg);
        }
        else
        {
            mainloop();
        }


    }

        return msg.wParam;
}


LRESULT CALLBACK BaseWin::ImpleWinProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

    switch(Msg)
    {
        case WM_CREATE:
             wmCreate(hwnd);
             break;

        case WM_COMMAND:
             wmCommand(wParam);
             break;


        case WM_LBUTTONDOWN:
             wmLButtonDown();
             break;

        case WM_RBUTTONDOWN:
             wmRButtonDown();
             break;


        case WM_KEYDOWN:
             wmKeyDown(wParam);
             break;

        case WM_DESTROY:
             wmDestroy();
             PostQuitMessage(0);
             break;


        default:
            return DefWindowProc(hwnd,Msg,wParam,lParam);


    }

    return 0;

}
