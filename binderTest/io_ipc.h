// IO_IPC.h


#ifndef IO_IPC_H
#define IO_IPC_H
#ifdef UNICODE
#undef UNICODE
#undef _UNICODE
#endif
#include <windows.h>
#include <tchar.h>
#include <string>
using namespace std;

#define SVC_MGR_ADD_SERVICE  100
#define SVC_MGR_CHECK_SERVICE 101

#define BINDER_SERVICE_MANAGER 0

typedef int(*HANDLER)(int, int*, int*);

HANDLER _proxyServerHandler;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if ( msg >= WM_USER )
			return _proxyServerHandler( msg - WM_USER, (int*)&wParam, (int*)&lParam);

	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}

HWND MakeWindow( string name, int show )
{
	HINSTANCE hInstance = GetModuleHandle(0);
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
	wc.hCursor = LoadCursor( 0, IDC_ARROW);
	wc.hIcon   = LoadIcon( 0, IDI_APPLICATION);
	wc.hInstance    = hInstance;
	wc.lpfnWndProc  = WndProc;
	wc.lpszClassName= _T("First");
	wc.lpszMenuName = 0;
	wc.style		= 0;

	RegisterClass( &wc ); 

	HWND hwnd = CreateWindowEx( 0,	_T("First"), name.c_str() , WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	0, 0, hInstance, 0); 

	ShowWindow( hwnd, show ); 
	return hwnd;
}


void ProcessMessage( HANDLER handler)
{
	_proxyServerHandler = handler;
	MSG msg;
	while( GetMessage( &msg, 0, 0, 0) ) 
	{
		TranslateMessage( &msg ),
		DispatchMessage(&msg);
	}
} 

void StartServer( string name, HANDLER handler, int show = SW_HIDE )
{
#ifdef _DEBUG
	printf("[DEBUG] %s Server Start...\n", name.c_str());
#endif

	MakeWindow(name, show);
	ProcessMessage(handler);
}

int FindServer( string name )
{
	HWND hwnd = FindWindow( 0, name.c_str() );

	if ( hwnd == 0 ) 
	{
		printf("[DEBUG] 실패 : %s Server를 찾을수 없습니다.\n", name.c_str());
		return -1;	
	}
	return (int)hwnd;
}

int SendServer( int serverid, int code, int param1, int param2 )
{
	return SendMessage( (HWND)serverid, code + WM_USER, param1, param2);
}
//-----------------------------
// mimic android

int get_service( string name )
{
	HWND hwnd = FindWindow( 0, name.c_str() );

	if ( hwnd == 0 ) 
	{
		printf("[DEBUG] 실패 : %s Server를 찾을수 없습니다.\n", name.c_str());
		return -1;	
	}
	return (int)hwnd;
}

void add_service( string name )
{
#ifdef _DEBUG
	printf("[DEBUG] %s Service register\n", name.c_str());
#endif

	MakeWindow(name, SW_HIDE);
}

int binder_call( int fd, int* msg, int* reply, int serverid, int code)
{
	if ( serverid == 0 )
	{
		if ( code == SVC_MGR_CHECK_SERVICE )
		{
			return get_service( reinterpret_cast<const char*>(msg));
		}
		else if ( code == SVC_MGR_ADD_SERVICE )
		{
			add_service( reinterpret_cast<const char*>(msg) );
			return 0;
		}
	}
	return SendMessage( (HWND)serverid, code + WM_USER, *msg, *reply);
}




void binder_loop( int fd, HANDLER handler )
{
	ProcessMessage(handler);
}

int binder_open( int size)
{
	// open() system call을 사용해서 바인더 드라이버를 오픈
	// mmap()으로 shared memory 생성
	return rand() % 10000;
}


#endif // IO_IPC_H
