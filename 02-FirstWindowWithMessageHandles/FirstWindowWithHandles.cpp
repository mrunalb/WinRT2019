//header
#include<windows.h>

//Declaration of callback function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) 
{
	WNDCLASSEX wndcls;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("MyClass");
	
	//Display message : Application started
	MessageBox(NULL, TEXT("Welcome to my Application"), TEXT("MessageCaptionBar"), MB_OK|MB_ICONINFORMATION);

	//initializasation of 12 members of wndcls
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.cbSize = sizeof(wndcls);
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = szClassName;
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	//Register above class
	RegisterClassEx(&wndcls);

	hwnd = CreateWindow(szClassName,
		TEXT("NOTEPAD"),
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

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[255];
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		wsprintf(str,TEXT("You are in : WM_CREATE"));
		MessageBox(hwnd,str,TEXT("MessageCaptionBar"),MB_OK|MB_ICONINFORMATION);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("You are in : WM_LBUTTONDOWN"));
		MessageBox(hwnd,str,TEXT("MessageCaptionBar"),MB_OK|MB_ICONINFORMATION);
		break;
	case WM_KEYDOWN:
		wsprintf(str, TEXT("You are in : WM_KEYDOWN"));
		MessageBox(hwnd, str, TEXT("MessageCaptionBar"), MB_OK | MB_ICONINFORMATION);
		break;
	}

	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}




