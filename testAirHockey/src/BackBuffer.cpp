//BackBuffer.cpp

#include "BackBuffer.h"

BackBuffer::BackBuffer(HWND hwnd, int width, int height)
{
    mHwnd=hwnd;
    mWidth=width;
    mHeight=height;

    HDC hwndDC=GetDC(hwnd);

    mHdc=CreateCompatibleDC(hwndDC);

    //now mHdc doesn't have the memory of bitmap

    mHsurface=CreateCompatibleBitmap(hwndDC, width, height);

    ReleaseDC(hwnd,hwndDC);

    mHoldObject=(HBITMAP)SelectObject(mHdc,mHsurface);

    HBRUSH white=(HBRUSH)GetStockObject(WHITE_BRUSH);
    HBRUSH oldBrush=(HBRUSH)SelectObject(mHdc,white);

    Rectangle(mHdc,0,0,width,height);

    SelectObject(mHdc,oldBrush);

}


HDC BackBuffer::getDC()
{
    return mHdc;
}


int BackBuffer::height()
{
    return mHeight;
}


int BackBuffer::width()
{
    return mWidth;
}

BackBuffer::~BackBuffer()
{
    SelectObject(mHdc,mHoldObject);
    DeleteObject(mHsurface);
    DeleteDC(mHdc);
}

void BackBuffer::present()
{
    HDC hwndDC=GetDC(mHwnd);

    BitBlt(hwndDC,0,0,mWidth,mHeight,mHdc,0,0,SRCCOPY);

    ReleaseDC(mHwnd,hwndDC);

}
