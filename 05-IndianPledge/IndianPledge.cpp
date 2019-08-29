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
	TEXTMETRIC tm;
	static int cyChar;
    static TCHAR str2[255][255];
    TCHAR strMsg[255];
	int i, j = 0;
	int color[255] = {RGB(255,125,0),RGB(255,255,255),RGB(0,255,0)};
	int x = 0;
	int y = 0;
	
	switch (iMsg)
	{
	case WM_CREATE:
		wsprintf(strMsg, TEXT("You are in WM_CREATE"));
		MessageBox(hwnd, strMsg, TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc,&tm);
		ReleaseDC(hwnd,hdc);
		cyChar=tm.tmHeight+tm.tmExternalLeading;
		
		wsprintf(&str2[0][0], TEXT("India Is my country."));
		wsprintf(&str2[1][0], TEXT("All Indians are my brothers and sisters."));
		wsprintf(&str2[2][0], TEXT("I love my country and "));
		wsprintf(&str2[3][0], TEXT("I am proud of its rich and varied heritage."));
		wsprintf(&str2[4][0], TEXT("I shall always strive to be worth of it."));
		wsprintf(&str2[5][0], TEXT("I shall give my parents, teachers and "));
		wsprintf(&str2[6][0], TEXT("all elders respect"));
		wsprintf(&str2[7][0], TEXT("and treat everyone with courtesy."));
		wsprintf(&str2[8][0], TEXT("To my country and my people,"));
		wsprintf(&str2[9][0], TEXT("I pledge my devotion."));
		wsprintf(&str2[10][0], TEXT("In their well being and prosperity alone,"));
		wsprintf(&str2[11][0], TEXT("lies my happiness."));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		
		SetTextColor(hdc, color[j]);
		for(i=0;i<12;i++)
		{	
			if(i%4 == 0)
			{
				SetTextColor(hdc, color[j]);
				j = j +1 ;
			}
			TextOut(hdc, 5 ,y, &str2[i][0], lstrlen(&str2[i][0]));
			y = y + cyChar;
		}
		
		
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
