//header files
#include<windows.h>

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
	wndcls.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndcls.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);

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

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	TCHAR str[] = TEXT("HELLO  WORLD...!");
	TCHAR strMsg[255];

	switch (iMsg)
	{
	case WM_CREATE:
		wsprintf(strMsg, TEXT("You are in WM_CREATE"));
		MessageBox(hwnd, strMsg, TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(strMsg, TEXT("You have pressed Left Button"));
		MessageBox(hwnd, strMsg, TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_KEYDOWN:
		wsprintf(strMsg, TEXT("You have pressed a key"));
		MessageBox(hwnd, strMsg, TEXT("Message"), MB_OK | MB_ICONINFORMATION);
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}