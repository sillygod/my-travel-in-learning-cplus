// win.cpp

#include "win.h"

Wnd::Wnd()
: mHwnd(NULL), mHDC(NULL), mMenu(NULL)
{
	mClassName[BUTTON]="BUTTON";
	mClassName[EDIT]="EDIT";
	mClassName[COMBOBOX]="COMBOBOX";
	mClassName[LISTBOX]="LISTBOX";
	mClassName[MDICLIENT]="MDICLIENT";
	mClassName[RichEdit]="RichEdit";
	mClassName[RICHEDIT_CLASS]="RICHEDIT_CLASS";
	mClassName[SCROLLBAR]="SCROLLBAR";
	mClassName[STATIC]="STATIC";
}

Wnd::~Wnd()
{
	if( IsWindow(mHwnd) )
		DestroyWindow(mHwnd);
}

const char* Wnd::getSystemClassName(SystemClass type)const
{
	return mClassName.find(type)->second;
}


void Wnd::setMenu(LPCTSTR menu){
    mMenu = ::LoadMenu(mWc.hInstance, menu);
}


bool Wnd::Register(const char* className /*="Default name"*/) //I don't know why here can't type ="Default name"
{
	mWc.cbClsExtra=0;
	mWc.cbWndExtra=0;
	mWc.style=CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
	mWc.lpszClassName=className; // if the name is unuseful, it will make error
	mWc.hInstance=GetModuleHandle(NULL);
	mWc.lpfnWndProc=staticWndProc;
	mWc.lpszMenuName=NULL;
	mWc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	mWc.hIcon=LoadIcon(0, IDI_APPLICATION);
	mWc.hCursor= LoadCursor(0, IDC_ARROW);

	if(!RegisterClass( &mWc ))
		return false;

	return true; // successful
}

bool Wnd::Create(int width/*640*/, int height/*320*/)
{
	mHwnd=CreateWindow(
		mWc.lpszClassName,
		"app",
		WS_OVERLAPPEDWINDOW | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		mMenu,
		mWc.hInstance,
		this); // store this pointer , it's very important


	if(!mHwnd) return false;

	ShowWindow(mHwnd, SW_NORMAL);
	UpdateWindow(mHwnd);

	return true;
}

WPARAM Wnd::Run()
{
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
			//
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK Wnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_CREATE:
		{
			break;
		}


		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}


LRESULT CALLBACK Wnd::staticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//use a trick lParam's store data to grab this pointer
	if(uMsg==WM_CREATE) SetWindowLong(hWnd, GWL_USERDATA, (LONG) ( (CREATESTRUCT FAR*)lParam )->lpCreateParams );

	Wnd *destination = (Wnd*) GetWindowLong(hWnd,GWL_USERDATA);

	if(destination) return destination->WndProc(hWnd, uMsg, wParam, lParam);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HWND Wnd::getHwnd()const
{
	return mHwnd;
}

Wnd* Wnd::getThis()const
{
	return (Wnd*)this;
}
