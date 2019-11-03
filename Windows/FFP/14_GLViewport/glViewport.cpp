//Assignment No.16 - Different glViewPort Positions of triangle

//Headers
#include <windows.h>
#include <gl/GL.h> //For compiler
#include <stdio.h>

#pragma comment(lib, "Opengl32.lib") //Linking OpenGL library - This statement is for Linker

//constants
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//Global variable declarations
HDC ghdc = NULL;
HGLRC ghrc = NULL; //Open GL Rendoring Context
bool gbActivWindow = false;
bool bIsFullScreen = false;
DWORD dwstyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
HWND ghwnd = NULL;
FILE *gpFile = NULL;

//Draw Functions
void drawTriangle();
//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function declarations
	int initialize();
	void display(); //for double buffer window

	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyOpenGLWindow");

	bool bDone = false;
	int iRet;

	//code 
	//Log file creation
	if (fopen_s(&gpFile, "Log.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Log file cannot be created"), TEXT("Log File Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Log file is successfully created \n");
	}

	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //CS_OWNDC : To tell OS that this DC is 
														 //specialized DC, so should not be discarded
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, //always keep fullscreen window on top of taskbar
		szAppName,
		TEXT("OpenGL Window By Vinit"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		100,
		100,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;
	iRet = initialize();

	if (iRet == -1)
	{
		//Choose pixel format failed
		fprintf(gpFile, "ChoosePixelFormat() Failed \n");
		DestroyWindow(hwnd);
	}
	else if (iRet == -2)
	{
		fprintf(gpFile, "SetPixelFormat() Failed \n");
		DestroyWindow(hwnd);
	}
	else if (iRet == -3)
	{
		fprintf(gpFile, "WglCreateContext() Failed \n");
		DestroyWindow(hwnd);
	}
	else if (iRet == -4)
	{
		fprintf(gpFile, "WglMakeCurrent() Failed \n");
		DestroyWindow(hwnd);
	}
	else
	{
		fprintf(gpFile, "initialize() function succeeded \n");
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//Gameloop
	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				//message loop
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
		}
		else
		{
			//Play the game
			if (gbActivWindow == true)
			{
				//update()
			}

			display();
		}
	}

	return((int)msg.wParam);
}
GLint h, w;
GLfloat step = 0.05f;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	//function declarations
	void resize(int, int);
	void ToggleFullScreen(void);
	void uninitialize(void);
	RECT rc;
	GetClientRect(hwnd, &rc);
	static int width;
	static int height;

	//code
	switch (iMsg)
	{
	case WM_SETFOCUS:
		gbActivWindow = true;
		break;
	case WM_KILLFOCUS:
		gbActivWindow = false;
		break;
	case WM_SIZE:
		w = width = LOWORD(lParam);
		h = height = HIWORD(lParam);
		resize(width, height);
		break;
	case WM_ERASEBKGND:
		return 0; //Don't call DefWindowProc - don't post WM_PAINT message
					//external painter will paint my window
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_NUMPAD0: //for 0 key
			glViewport(0, 0, w, h);
			break;
		case VK_NUMPAD1: //For 1 key
			//resize(rc.right - rc.left, rc.bottom - rc.top, 1);
			glViewport(0, height / 2, width / 2, height / 2);
			break;
		case VK_NUMPAD2: //For 2 key
			glViewport(0, h / 2, w, h / 2);
			break;
		case VK_NUMPAD3: //For 3 key
			glViewport(0, 0, w, h / 2);
			break;
		case VK_NUMPAD4: //For 4 key
			glViewport(w / 2, h / 2, w / 2, h / 2);
			break;
		case VK_NUMPAD5: //For 5 key
			glViewport(0, 0, w / 2, h / 2);
			break;
		case VK_NUMPAD6: //For 6 key
			glViewport(w / 2, 0, w / 2, h / 2);
			break;
		case VK_NUMPAD7: //For 7 key
			glViewport(0, 0, w / 2, h);
			break;
		case VK_NUMPAD8: //For 8 key
			glViewport(w / 2, 0, w / 2, h);
			break;
		case VK_NUMPAD9: //For 9 key
			break;
		case VK_SPACE:
			step = step + step;
			break;
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		case 0x46: //F key
			ToggleFullScreen();
			break;
		}
		break;
	case WM_DESTROY:
		uninitialize();
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	MONITORINFO mi;

	if (bIsFullScreen == false)
	{
		dwstyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwstyle & WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };
			if (GetWindowPlacement(ghwnd, &wpPrev)
				&& GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwstyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd,
					HWND_TOP,
					mi.rcMonitor.left,
					mi.rcMonitor.top,
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
		bIsFullScreen = true;
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwstyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,
			HWND_TOP,
			0,
			0,
			0,
			0,
			SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER
		);
		ShowCursor(TRUE);
		bIsFullScreen = false;
	}
}

int initialize(void)
{
	//function declarations
	void resize(int, int);

	//variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	INT iPixelFormatIndex;

	//code
	//initialize pfd structure
	//initialize pfd members to 0
	ZeroMemory((void *)&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	//OR
	//memset((void *)&pfd, NULL, size(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	ghdc = GetDC(ghwnd);
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0)
	{
		return -1;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		return -2;
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		return -3;
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		return -4;
	}

	//Clear screen by Open GL color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//warm up call to resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	return 0;
}

void resize(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}
GLfloat angle = 0.0f;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.6f, 0.0f, -8.0f);
	glLoadIdentity();
	glRotatef(angle,0.0f,1.0f,0.0f);
	drawTriangle();
	angle = angle + step;
	SwapBuffers(ghdc);
}

void uninitialize(void)
{
	//Check whether fullscreen or not and if it is then restore to normal size and then proceed for uninitialization
	if (bIsFullScreen == true)
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwstyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,
			HWND_TOP,
			0,
			0,
			0,
			0,
			SWP_NOZORDER | SWP_NOMOVE | SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOOWNERZORDER);
		ShowCursor(TRUE);
	}

	//safe uninitialize
	//break the current context
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "Log.txt file closed successful");
		fclose(gpFile);
		gpFile = NULL;
	}
}

void drawTriangle()
{
	glBegin(GL_TRIANGLES);

	//vertex 1
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.5f);

	//vertex 2
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);

	//vertex 3
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, -0.5f);

	
	glEnd();
}