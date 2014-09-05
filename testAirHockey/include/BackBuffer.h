//BackBuffer.h

#ifndef BACKBUFFER_H
#define BACKBUFFER_H

#include <windows.h>

class BackBuffer
{
    public:
        HDC getDC();
        void present();
        int width();
        int height();

        BackBuffer(HWND hwnd, int width, int height);
        ~BackBuffer();


    private:
    // to forbid copy of bitmap, in this class will make this behavior slow
        BackBuffer(const BackBuffer& rhs);
        BackBuffer& operator=(const BackBuffer& rhs);


    //
        HWND    mHwnd;
        HDC     mHdc;
        HBITMAP mHsurface;
        HBITMAP mHoldObject;
        int     mWidth;
        int     mHeight;

};


#endif// BackBuffer.h
