//header files
#include<windows.h>
#include"FirstSplashScreen.h"

//declare global callback function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLineName, int iCmdShow)
{
	WNDCLASSEX wndcls;
	MSG msg;
	HWND hwnd;
	TCHAR className[] = TEXT("CLASS_NAME");

	//declare 12 members of WNDCLASSEX
	wndcls.cbSize = sizeof(WNDCLASSEX);
	wndcls.hInstance = hInstance;
	wndcls.lpszClassName = className;
	wndcls.lpszMenuName = NULL;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc = WndProc;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndcls.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndcls.hCursor = LoadCursor(NULL,IDC_ARROW);

	RegisterClassEx(&wndcls);

	hwnd = CreateWindow(className,
		TEXT("ApplicationMatrix"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	
	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR strMsg[255];
	HINSTANCE hInstance;
	HDC hdc,cdc;
	static HBITMAP hbitSplashScreen;
	BITMAP bitSplashScreen;
	PAINTSTRUCT ps;
	RECT rc;

	switch (iMsg)
	{
	case WM_CREATE:
		wsprintf(strMsg, TEXT("You are in WM_CREATE"));
		MessageBox(hwnd, strMsg, TEXT("Message"), MB_OK | MB_ICONINFORMATION);	
		hInstance = GetModuleHandle(NULL);
		hbitSplashScreen = LoadBitmap(hInstance,MAKEINTRESOURCE(MYBITMAP));
		if (hbitSplashScreen == NULL)
		{
			MessageBox(hwnd, TEXT("Bit map did not load!"), TEXT("ERROR"), MB_OK);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(strMsg,TEXT("You have pressed Left Button"));
		MessageBox(hwnd, strMsg, TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_KEYDOWN:
		wsprintf(strMsg, TEXT("You have pressed a key"));
		MessageBox(hwnd, strMsg, TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		cdc = CreateCompatibleDC(NULL);
		SelectObject(cdc, hbitSplashScreen);
		GetObject(hbitSplashScreen, sizeof(BITMAP), &bitSplashScreen);
		StretchBlt(hdc, 0 , 0, rc.right - rc.left, rc.bottom - rc.top, cdc, 0, 0, bitSplashScreen.bmWidth, bitSplashScreen.bmHeight, SRCCOPY);
		//SetTextColor(hdc, RGB(0,255,0));
		SetBkColor(hdc, RGB(0,0,0));
		DeleteObject(cdc);
		EndPaint(hwnd, &ps);
		break;
	}
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
