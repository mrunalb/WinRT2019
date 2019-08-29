#include<windows.h>  //header 

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //declaration of callback function 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdLine) //main
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	MessageBox(NULL, TEXT("Welcome to my Application"), TEXT("MessageCaptionBar"), MB_OK | MB_ICONINFORMATION);

	//following are 12 members of class:wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);  //Registering the declared class

	//create wondow(class name,window name,style,x,y,w,h,Parent,menu.instance,lparam)
	hwnd = CreateWindow(
		szAppName,
		TEXT("MyApplication"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//show the created window
	ShowWindow(hwnd, iCmdLine);

	//update window
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
	static int iFlag = 0;
	static RECT rc;
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush;
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		wsprintf(str, TEXT("You are in : WM_CREATE"));
		MessageBox(hwnd, str, TEXT("MessageCaptionBar"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("You are in : WM_LBUTTONDOWN"));
		MessageBox(hwnd, str, TEXT("MessageCaptionBar"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'a':
			MessageBox(hwnd, TEXT("a pressed"), TEXT("MessageCaptionBar"), MB_OK | MB_ICONINFORMATION);
			break;
		case 'r':
			iFlag = 1;
			InvalidateRect(hwnd,&rc,true);
			break;
		case 'g':
			iFlag = 2;
			InvalidateRect(hwnd, &rc, true);
			break;
		case 'b':
			iFlag = 3;
			InvalidateRect(hwnd, &rc, true);
			break;
		case 'c':
			iFlag = 4;
			InvalidateRect(hwnd, &rc, true);
			break;
		case 'm':
			iFlag = 5;
			InvalidateRect(hwnd, &rc, true);
			break;
		case 'y':
			iFlag = 6;
			InvalidateRect(hwnd, &rc, true);
			break;
		case 'k':
			iFlag = 7;
			InvalidateRect(hwnd, &rc, true);
			break;
		case 'w':
			iFlag = 8;
			InvalidateRect(hwnd, &rc, true);
			break;
		default:   //default case 
			iFlag = 0;
			InvalidateRect(hwnd, &rc, true);
			break;
		}
		break;
	case WM_PAINT:
		GetClientRect(hwnd,&rc);
		hdc = BeginPaint(hwnd,&ps);
		switch (iFlag)
		{
		case 1:
			hBrush = CreateSolidBrush(RGB (255,0,0));
			SelectObject(hdc, hBrush);
			FillRect(hdc,&rc,hBrush);
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 8:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 0:  
			hBrush = CreateSolidBrush(RGB(125,125,125));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		}
		EndPaint(hwnd,&ps);
		break;
	case WM_KEYDOWN:
		wsprintf(str, TEXT("You are in : WM_KEYDOWN"));
		MessageBox(hwnd, str, TEXT("MessageCaptionBar"), MB_OK | MB_ICONINFORMATION);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}







