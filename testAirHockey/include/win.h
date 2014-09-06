//win.h



//the intention of this class is practice..
//I want to be familiar with win32, although not all. However, try to realize as deep
//as possibel

#ifndef WIN_H
#define WiN_H

#include "main.h"

class Wnd
{
    public:

        enum SystemClass  // the number represent the window type
        {
            BUTTON=0,
            EDIT,
            COMBOBOX,
            LISTBOX,
            MDICLIENT,
            RichEdit,
            RICHEDIT_CLASS,
            SCROLLBAR,
            STATIC
        };

        // public method should be a role of interface
        Wnd(); //initial the wndclass data
        virtual ~Wnd();


        HWND getHwnd()const; // get hwnd;
        HINSTANCE gethInstance()const { return mWc.hInstance; };
        void setMenu(LPCTSTR menu);
        Wnd* getThis()const; // get this pointer
        const char* getSystemClassName(SystemClass type)const; // get the predefined class name

        bool Register(const char* className="Default name");
        bool Create(int width=640, int height=320); // create window, default 640x320 you can pass the parameter
        // I think maybe the Create function should include the register?

        virtual WPARAM Run(); // run message loop

    protected:
        virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // message handle

    private:
        static LRESULT CALLBACK staticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        HWND mHwnd;
        HDC mHDC;
        HMENU mMenu;

        WNDCLASS mWc;
        std::map<SystemClass,const char*> mClassName; //be initialize in the constructor
};


#endif
