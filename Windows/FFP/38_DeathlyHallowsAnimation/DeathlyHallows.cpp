#include<windows.h>
#include<stdio.h>
#include<gl/GL.h>
#define _USE_MATH_DEFINES 1
#include<math.h>
#include<gl/GLU.h>

#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND ghwnd;
HDC ghdc = NULL;
HGLRC ghrc = NULL; //OpenGL Rendering Context
FILE *gpfile;
DWORD dwstyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool bFullScreen = false;
bool GbActiveWindow = false;
bool GbFullScreen = false;

void ToggleFullScreen(void);
void resize(int, int);
void display(void);
void uninitialize();
void kundali();
void drawTriangles();
void drawRect();
void drawGraphPaper(GLfloat step);
void drawCircle(GLfloat inradius);
void drawVerticalLine();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//fuction declarations
	int initialize(void);


	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd = NULL;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//variable declarations 2
	bool bDone = false;
	int iRet = 0;

	//FullScreen Global 
	void ToggleFullScreen(void);
	bool bFullScreen = false;
	WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };


	//code

	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName,
		TEXT("OpenGL Window by Vinit"),
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
	if (fopen_s(&gpfile, "Log.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Log File Cannot be Created"), TEXT("Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpfile, "Log File Successfully Created\n");
	}
	iRet = initialize();
	if (iRet == -1)
	{
		fprintf(gpfile, "Choose Pixel Format Failed\n");
	}
	else if (iRet == -2)
	{
		fprintf(gpfile, "Set Pixel Format Failed\n");
	}
	else if (iRet == -3)
	{
		fprintf(gpfile, "wglCreateContext failed\n");
	}
	else if (iRet == -4)
	{
		fprintf(gpfile, "wglMakeCurrent failed\n");
		DestroyWindow(hwnd);
	}
	else
	{
		fprintf(gpfile, "Initialization Successful\n");
	}
	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//UpdateWindow(hwnd);
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
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (GbActiveWindow == true)
			{
				//Here call update
			}

			//Here call display for DoubleBuffer
			display();

		}


	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//code
	switch (iMsg)
	{
	case WM_SETFOCUS:
		GbActiveWindow = true;
		break;
	case WM_KILLFOCUS:
		GbActiveWindow = false;
		break;
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
	case WM_ERASEBKGND:
		return 0;
		// This should be done only in single buffering
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		uninitialize();
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			MessageBox(hwnd, TEXT("This is Escape"), TEXT("MAIN2"), MB_OK);
			DestroyWindow(hwnd);
			break;
		case 0x46:
			ToggleFullScreen();
			MessageBox(hwnd, TEXT("This is FullScreen"), TEXT("FS"), MB_OK);
			break;
		}
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

int initialize(void)
{
	//function declaration
	void resize(int, int);
	//variable declaration
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;
	//code
	//initialize pfd structure / Filling Form
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
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
		return -1;
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == false)
		return -2;
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
		return -3;
	if (wglMakeCurrent(ghdc, ghrc) == false)
		return -4;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	resize(WIN_WIDTH, WIN_HEIGHT);

	return 0;
}

void resize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}
GLfloat i = 0.0f;
GLfloat step = 1.0f / 20;
GLfloat angle = 0.0f;
void display(void)
{
	//if (angle > 360.0f)
	//	angle = 0.0f;
	//GLfloat A, B, C;  // Vertices of Triangle
	GLfloat X1 = 0.0f, Y1 = 0.5f; //C
	GLfloat X2 = -0.5f, Y2 = -0.5f; //B    
	GLfloat X3 = 0.5f, Y3 = -0.5f; //A
	GLfloat X4 = 0.5f, Y4 = 0.5f;
	GLfloat a, b, c ,d;    // Length  of BC AC AB
	GLfloat incenterx, incentery;
	GLfloat s;
	GLfloat inradius;

	// temp = sqrt( ( (20*20) + (15*15) ) );
	a = (GLfloat)sqrt(((X2 - X1)*(X2 - X1) + (Y2 - Y1)*(Y2 - Y1)));

	b = (GLfloat)sqrt(((X3 - X1)*(X3 - X1) + (Y3 - Y1)*(Y3 - Y1)));

	c = (GLfloat)sqrt(((X3 - X2)*(X3 - X2) + (Y3 - Y2)*(Y3 - Y2)));
	incenterx = ((a*X3) + (b*X2) + (c*X1)) / (a + b + c);
	incentery = ((a*Y3) + (b*Y2) + (c*Y1)) / (a + b + c);
	
	s = (a + b + c) / 2;
	inradius = (GLfloat)sqrt(s*(s - a)*(s - b)*(s - c)) / s;

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.5f);
	//glScalef(1.3f, 1.2f, 0.0f);
		
	glRotatef(angle,0.0f,1.0f,0.0f);
	drawTriangles();
	glPointSize(1.0f);
	/*glBegin(GL_POINTS);
	glVertex3f(incenterx,incentery,0.0f);
	glEnd();*/
	
	glLoadIdentity();
	glTranslatef(incenterx, incentery, -2.5f);
	
	//glScalef(1.3f, 1.2f, 0.0f);
	
	glRotatef(angle, 1.0f, 0.0f, 0.0f);
	//glTranslatef(incenterx, incentery, 0.0f);
	drawCircle(inradius);

	//ExCircle
	
	X1 = -0.5f, Y1 = 0.5f;  //D
	X2 = -0.5f, Y2 = -0.5f; //B    
	X3 = 0.5f, Y3 = -0.5f; //C
	X4 = 0.5f, Y4 = 0.5f; //E

	a = (GLfloat)sqrt(((X2 - X1)*(X2 - X1) + (Y2 - Y1)*(Y2 - Y1))); //DE
	
	b = (GLfloat)sqrt(((X3 - X2)*(X3 - X2) + (Y3 - Y2)*(Y3 - Y2))); //DB
	
	c = (GLfloat)sqrt(((X3 - X4)*(X3 - X4) + (Y3 - Y4)*(Y3 - Y4))); //BC
	
	d = (GLfloat)sqrt(((X4 - X1)*(X4 - X1) + (Y4 - Y1)*(Y4 - Y1))); //EC
	
	incenterx = ((a*X2) + (b*X1) + (c*X3) + (d*X4)) / (a + b + c + d);
	incentery = ((a*Y2) + (b*Y1) + (c*Y2) + (d*Y4)) / (a + b + c + d);
	
	glLoadIdentity();
	glTranslatef(incenterx, incentery, -2.5f);
	
	drawVerticalLine();

	angle = angle + 0.1f;
	SwapBuffers(ghdc);

}

void uninitialize(void)
{
	if (GbFullScreen == true)
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
	if (gpfile)
	{
		fprintf(gpfile, "fclose Successful");
		fclose(gpfile);
		gpfile = NULL;
	}
}

void ToggleFullScreen(void)
{
	MONITORINFO mi;
	if (bFullScreen == false)
	{
		dwstyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwstyle && WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwstyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left,
					mi.rcMonitor.top,
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
		bFullScreen = true;
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwstyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
		ShowCursor(TRUE);
		bFullScreen = false;
	}
}

void kundali()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();
}

void drawTriangles()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(0.0f, 0.5f , 0.0f);
	glVertex3f(-0.5f , -0.5f , 0.0f);
	glVertex3f(0.5f , -0.5f , 0.0f);
	glEnd();
}

void drawRect()
{
	glBegin(GL_LINE_LOOP);
	
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f , 0.5f , 0.0f);
	glVertex3f(0.5f , 0.5f , 0.0f);
	glVertex3f(0.5f , -0.5f , 0.0f);
	glVertex3f(-0.5f , -0.5f , 0.0f);
	glEnd();
}

void drawCircle(GLfloat inradius)
{
	GLfloat i;
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (i = 0.0f; i < 2 * M_PI ; i += 0.1f)
	{
		glVertex3f((GLfloat)cos(i)*inradius,(GLfloat)sin(i)*inradius,0.0f);
	}
	glEnd();
}

void drawGraphPaper(GLfloat step)
{
	glLineWidth(2.0f);
	glBegin(GL_LINES);

	//GL_POINTS

	//X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	//Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glEnd();

	glLineWidth(1.0f);
	glBegin(GL_LINES);
	//Top Horizontal

	for (float i = 0.0f + step; i < 1.0f; i += step)
	{

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, i, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, i, 0.0f);
	}

	//Bottom Horizontal
	for (float i = 0.0f - step; i > -1.0f; i -= step)
	{

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, i, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, i, 0.0f);
	}
	//Left Vertical

	for (float i = 0.0f - step; i > -1.0f; i -= step)
	{

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(i, 1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(i, -1.0f, 0.0f);
	}
	//Right Vertical

	for (float i = 0.0f + step; i < 1.0f; i += step)
	{

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(i, 1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(i, -1.0f, 0.0f);
	}
	glEnd();
}

void drawVerticalLine()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glEnd();
}