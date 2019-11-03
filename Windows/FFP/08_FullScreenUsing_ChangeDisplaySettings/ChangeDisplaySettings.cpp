#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//fullscreen
void ToggleFullScreen(void);

bool bFullScreen = false;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
DWORD dwstyle;
HWND ghwnd = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

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

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
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

	ghwnd = hwnd;

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
	switch (iMsg)
	{
	case WM_CREATE:
		//MessageBox(hwnd, TEXT("This is Create Window\nTop Z Order"), TEXT("MAIN"), MB_OK);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//MessageBox(hwnd, TEXT("This is Escape"), TEXT("MAIN2"), MB_OK);
			DestroyWindow(hwnd);
			break;
		case 0x46:
			ToggleFullScreen();
			//MessageBox(hwnd, TEXT("This is FullScreen"), TEXT("FS"), MB_OK);
			break;
		}
	case WM_LBUTTONDOWN:
		//MessageBox(hwnd, TEXT("This is Left Mouse Button"), TEXT("LB"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		//MessageBox(hwnd, TEXT("This is Right Mouse Button"), TEXT("RB"), MB_OK);
		break;
	case WM_DESTROY:
		//MessageBox(hwnd, TEXT("Mela"), TEXT("Gela Kamatun"), MB_OK);
		PostQuitMessage(0);

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	DEVMODE devMode = { sizeof(DEVMODE) };

	if (bFullScreen)
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwstyle | WS_OVERLAPPEDWINDOW);
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 800, 600, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
		bFullScreen = 0;
	}
	else
	{
		dwstyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwstyle & WS_OVERLAPPEDWINDOW)
		{
			EnumDisplaySettings(NULL, 0, &devMode);
			ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
			SetWindowLong(ghwnd, GWL_STYLE, dwstyle & ~WS_OVERLAPPEDWINDOW);
			ShowCursor(FALSE);
		}
		bFullScreen = 1;
	}
}

