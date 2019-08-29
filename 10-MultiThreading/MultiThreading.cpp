#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("MyClass");
	
	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;
	
	RegisterClassEx(&wndclass);
	
	hwnd = CreateWindow(szClassName, 
	TEXT("My Application"), 
	WS_OVERLAPPEDWINDOW, 
	CW_USEDEFAULT, 
	CW_USEDEFAULT, 
	CW_USEDEFAULT, 
	CW_USEDEFAULT, 
	NULL, 
	NULL, 
	hInstance, 
	NULL);
	
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}
 
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;
	
	switch(iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
			hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
			break;
		case WM_LBUTTONDOWN:
			MessageBox(hwnd, TEXT("Left Button Pressed"), TEXT("Message Caption Bar"), MB_OK);
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID PARAM)
{
	HDC hdc;
	long int i;
	TCHAR str[255];
	HWND hwnd;
	
	hdc = GetDC((HWND)PARAM);
	SetTextColor(hdc, RGB(0,255,255));
	SetBkColor(hdc, RGB(0,0,0));
	
	for(i=0; i<4294967295; i++)
	{
		wsprintf(str, TEXT("ThreadOne ---> Increasing Order : %ld"),i);
		TextOut(hdc, 5, 5, str, lstrlen(str));
	}
	ReleaseDC(hwnd, hdc);
	return (0);
}

DWORD WINAPI ThreadProcTwo(LPVOID PARAM)
{
	HDC hdc;
	long int i;
	TCHAR str[255];
	HWND hwnd;
	
	hdc = GetDC((HWND)PARAM);
	SetTextColor(hdc, RGB(0,255,255));
	SetBkColor(hdc, RGB(0,0,0));
	
	for(i=4294967295; i<=0; i--)
	{
		wsprintf(str, TEXT("ThreadTwo ---> Decreasing Order : %ld"),i);
		TextOut(hdc, 5, 25, str, lstrlen(str));
	}
	ReleaseDC(hwnd, hdc);
	return (0);
}


