#include<windows.h>  //header 
#define MY_TIMER 101;

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
	static RECT temp_rc;
	static int iWidth = 0;
	TCHAR str10[255];

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
		SetTimer(hwnd, 101, 1000, NULL);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("You are in : WM_LBUTTONDOWN"));
		MessageBox(hwnd, str, TEXT("MessageCaptionBar"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_TIMER:
		KillTimer(hwnd, 101);
	
		
		if (iFlag == 9)
		{
			iFlag = 0;
			temp_rc.left = rc.left;
			temp_rc.right = rc.left;
			temp_rc.top = rc.top;
			temp_rc.bottom = rc.bottom;
			InvalidateRect(hwnd, &rc, true);
		}
		//wsprintf(str10, TEXT("value of iFlag : %d"),iFlag);
		//MessageBox(hwnd,str10,TEXT("MSG"),MB_OK);
		iFlag = iFlag + 1;
		iWidth = (rc.right - rc.left)/ 8;
		temp_rc.bottom = rc.bottom;
		temp_rc.top = rc.top;
		temp_rc.left = temp_rc.right;
		temp_rc.right = temp_rc.left + iWidth;
		//rc.left = temp_rc.right;
				
		//wsprintf(str10, TEXT("value of iFlag : %d"),iFlag);
		//MessageBox(hwnd,str10,TEXT("MSG"),MB_OK);
		
		//if(iFlag!=0)
		//{
			InvalidateRect(hwnd, &temp_rc, true);
		//}

		SetTimer(hwnd, 101, 1500, NULL);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		
		hdc = BeginPaint(hwnd, &ps);
		switch (iFlag)
		{
		/*case 0:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &temp_rc, hBrush);
			break;*/
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0)); //red
			SelectObject(hdc, hBrush);
			FillRect(hdc, &temp_rc, hBrush);
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0)); //green
			SelectObject(hdc, hBrush);
			FillRect(hdc, &temp_rc, hBrush);
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255)); //blue
			SelectObject(hdc, hBrush);
			FillRect(hdc, &temp_rc, hBrush);
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255)); // cyan
			SelectObject(hdc, hBrush);
			FillRect(hdc, &temp_rc, hBrush);
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255)); // pink
			SelectObject(hdc, hBrush);
			FillRect(hdc, &temp_rc, hBrush);
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0)); // yellow
			SelectObject(hdc, hBrush);
			FillRect(hdc, &temp_rc, hBrush);
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(255,128,0)); //orange
			SelectObject(hdc, hBrush);
			FillRect(hdc, &temp_rc, hBrush);
			break;
		case 8:
			hBrush = CreateSolidBrush(RGB(255, 255, 255)); // white
			SelectObject(hdc, hBrush);
			FillRect(hdc, &temp_rc, hBrush);
			break;
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		wsprintf(str, TEXT("You are in : WM_KEYDOWN"));
		MessageBox(hwnd, str, TEXT("MessageCaptionBar"), MB_OK | MB_ICONINFORMATION);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}









