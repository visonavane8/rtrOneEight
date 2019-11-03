#include<windows.h>
#include<stdio.h>
#include<gl/GL.h>
#define _USE_MATH_DEFINES 1
#include<math.h>
#include<gl/GLU.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

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

void Rect();
void Tri();
void graph();

GLfloat tx, ty, tz;
GLfloat sx, sy, sz;
GLfloat theta;


//Custom Matrices
GLfloat Identity_matrix[16] = {
	1.0f , 0.0f, 0.0f, 0.0f,
	0.0f , 1.0f, 0.0f, 0.0f,
	0.0f , 0.0f, 1.0f, 0.0f,
	0.0f , 0.0f, 0.0f, 1.0f,
};

GLfloat Translation_matrix[16] = {
	1.0f , 0.0f, 0.0f, tx,
	0.0f , 1.0f, 0.0f, ty,
	0.0f , 0.0f, 1.0f, tz,
	0.0f , 0.0f, 0.0f, 1.0f,
};

GLfloat Scale_matrix[16] = {
	sx , 0.0f, 0.0f, 0.0f,
	0.0f , sy, 0.0f, 0.0f,
	0.0f , 0.0f, sz, 0.0f,
	0.0f , 0.0f, 0.0f, 1.0f,
};

GLfloat Rotation_matrix_x[16] = {
	1.0f , 0.0f, 0.0f, 0.0f,
	0.0f , cos(theta), -sin(theta), 0.0f,
	0.0f , sin(theta), cos(theta), 0.0f,
	0.0f , 0.0f, 0.0f, 1.0f,
};

GLfloat Rotation_matrix_y[16] = {
	cos(theta) , 0.0f, sin(theta), 0.0f,
	0.0f , 1.0f, 0.0f, 0.0f,
	-sin(theta) , 0.0f, cos(theta), 0.0f,
	0.0f , 0.0f, 0.0f, 1.0f,
};

GLfloat Rotation_matrix_z[16] = {
	cos(theta) , -sin(theta), 0.0f, 0.0f,
	sin(theta) , -cos(theta), 0.0f, 0.0f,
	0.0f , 0.0f, 1.0f, 0.0f,
	0.0f , 0.0f, 0.0f, 1.0f,
};

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

			//Here call display
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
		//case WM_PAINT:
			//display(); // This should be done only in single buffering
			//break;
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
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		uninitialize();
		PostQuitMessage(0);
		break;
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

	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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
	if (angle > 360.0f)
		angle = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	graph();
	//glLoadIdentity();
	glLoadMatrixf(Identity_matrix);
	glMultMatrixf(Translation_matrix);
	//glTranslatef(0.5f, 0.0f, 0.0f);
	glRotatef(angle,1.0f,0.0f,0.0f);
	Rect();

	//glLoadIdentity();
	glLoadMatrixf(Identity_matrix);
	glTranslatef(-0.5f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	Tri();

	glFlush();
	SwapBuffers(ghdc);
	angle += 0.1f;
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

void Rect()
{
	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.4f, 0.4f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.4f, 0.4f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.4f, -0.4f, 0.0f);

	glEnd();

}

void Tri()
{
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.4f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.4f, -0.4f, 0.0f);
	glEnd();

}

void graph()
{
	static GLfloat step = 1.0f / 20;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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

	glFlush();

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

	glFlush();
}