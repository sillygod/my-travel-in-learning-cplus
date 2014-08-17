//baseWin.h

#ifndef BASEWIN_H
#define BASEWIN_H

#include <windows.h>

class BaseWin
{
    public:

        BaseWin();
        virtual ~BaseWin(){};
        // window message
        virtual void wmKeyDown(WPARAM wParam){};
        virtual void wmCreate(HWND hwnd){};
        virtual void wmLButtonDown(){};
        virtual void wmRButtonDown(){};
        virtual void wmCommand(WPARAM wParam){};
        virtual void wmDestroy(){};
        virtual void mainloop(){};



        //
        void setMenu(HINSTANCE hInst,int menuID);
        void regWindow(HINSTANCE hInst, LPCTSTR className,WNDPROC WinProc);
        void createWindow(HINSTANCE hInst ,LPCTSTR WindowName, int width, int height);
        void showWindow(int cmdShow);
        WPARAM run();

    protected:
        LRESULT CALLBACK ImpleWinProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        HWND mHwnd;
    private:
        HMENU mMenu;
        WNDCLASSEX mWndClsEx;


};


#endif //BASEWIN_H
