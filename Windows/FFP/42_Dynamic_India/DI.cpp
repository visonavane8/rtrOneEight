#include<windows.h>
#include<stdio.h>
#include<gl/GL.h>
#define _USE_MATH_DEFINES 1
#include<math.h>
#include<gl/GLU.h>

//#include<sound.h>
#pragma comment (lib,"winmm.lib")


struct india {

	GLfloat Top, NTop, Mid;
	GLfloat Bottom, NBottom;
	GLfloat R, G, B;
	GLfloat left;

};

struct jet {
	GLfloat top;
	GLfloat mid;
	GLfloat bottom;
	GLfloat left;
	GLfloat wmid;
	GLfloat right;

};

struct smk {
	GLfloat top, bottom, left, right;
	GLfloat R, G, B;
};

#define OO glColor3f(1.0f, 0.4f, 0.0f);
#define WW glColor3f(1.0f, 1.0f, 1.0f);
#define GG glColor3f(0.0f,1.0f,0.0f);
#define GR glColor3f(0.5f, 0.5f, 0.5f);
#define W  glColor3f(1.0f, 1.0f, 1.0f);
#define O  glColor3f(1.0f,0.4f,0.0f);
#define GGG glColor3f(0.0f,1.0f,0.0f);
#define CVD glColor3f(CV,CV,CV);


#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//LPCWSTR audio = (LPCWSTR)"AMPW.WAV";

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

//India 
void drawI(bool );
void drawN(bool );
void drawD(bool ,bool ,GLfloat);
void drawI2(bool );
void drawA(bool );
void drawJet(struct jet);
void drawSmoke(struct smk);

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

GLfloat speed = 0.0001f;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		PlaySound(TEXT("AMPW.WAV"), NULL, SND_FILENAME | SND_ASYNC);
		break;
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
			//MessageBox(hwnd, TEXT("This is Escape"), TEXT("MAIN2"), MB_OK);
			DestroyWindow(hwnd);
			break;
		case 0x46:
			ToggleFullScreen();
			//MessageBox(hwnd, TEXT("This is FullScreen"), TEXT("FS"), MB_OK);
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
	MONITORINFO mi;
	
	resize(WIN_WIDTH, WIN_HEIGHT);
	if (bFullScreen == false)
	{
		//speed = 0.001f;
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
	return 0;
}
bool flag = false;
void resize(int width, int height)
{
	if (flag == false)
	{
		flag = true;
	}
	else
	{
		speed = speed + 0.0001f;
	}
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}
GLfloat tx1 = -0.6f, ty1 = 0.0f;
GLfloat tx2 = -0.6f, ty2 = 0.0f;
GLfloat tx3 = -0.6f, ty3 = 0.0f;

GLfloat ix = -1.5f;
GLfloat ny = 1.5f;
GLfloat i2y = -1.5f; // For Moving India
GLfloat ax = 1.7f;
GLfloat ColorValue = 0.0f;

bool p1 = false, p2 = false, p3 = false ; // phase
bool CC = false;
bool idone = false, ndone = false, ddone = false, i2done = false, adone = false;
bool danimedone = false;

void display(void)
{
	
	
	//PlaySound();
	
	if (p2 == true)
	{
		CC = true;
	}
	struct smk o;
	struct smk w;
	struct smk g;
//Orange
	struct jet one;
	one.top = 0.7f;
	one.mid = 0.6f;	//Y
	one.bottom = 0.5f;
	one.left = -0.9f;
	one.wmid = -0.7f; //X
	one.right = -0.5f;

	o.right = one.left - 0.07f;
	o.left = o.right - 1.0f;
	o.top = one.top + 0.018f;
	o.bottom = one.bottom + 0.017f;
	o.R = 1.0f;
	o.G = 0.5f;
	o.B = 0.0f;
	
//White
	struct jet two;
	two.top = 0.1f;
	two.mid = 0.0f;	//Y
	two.bottom = -0.1f;
	two.left = -0.9f;
	two.wmid = -0.7f; //X
	two.right = -0.5f;

	w.right = two.left - 0.07f;
	w.left = w.right - 1.0f;
	w.top = two.top;
	w.bottom = two.bottom;
	w.R = 1.0f;
	w.G = 1.0f;
	w.B = 1.0f;

//Green
	struct jet three;
	three.top = -0.5f;
	three.mid = -0.6f;	//Y
	three.bottom = -0.7f;
	three.left = -0.9f;
	three.wmid = -0.7f; //X
	three.right = -0.5f;

	g.right = three.left - 0.07f;
	g.left = g.right - 1.0f;
	g.top = three.top - 0.017f;
	g.bottom = three.bottom - 0.018f;
	g.R = 0.0f;
	g.G = 1.0f;
	g.B = 0.0f;

//Code
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
//I
	glLoadIdentity();
	glTranslatef(ix, 0.0f, -2.5f);
	glScalef(1.3f, 1.2f, 0.0f);
	drawI(CC);
	if (ix < 0.0f)
	{
		ix = ix + 0.001f;
	}
	else
		idone = true;
//N
	glLoadIdentity();
	glTranslatef(0.0f, ny, -2.5f);
	glScalef(1.3f, 1.2f, 0.0f);
	drawN(CC);
	if (idone == true && ny > 0.0f)
		ny = ny - 0.001f;
	if(ny < 0.0f)
		ndone = true;
//D
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.5f);
	glScalef(1.3f, 1.2f, 0.0f);
	drawD(CC, danimedone, ColorValue);
	if (adone == true && ColorValue < 1.0f)
		ColorValue += 0.001f;
	if (ColorValue > 1.0f)
		ddone = true;
//I
	glLoadIdentity();
	glTranslatef(0.0f, i2y, -2.5f);
	glScalef(1.3f, 1.2f, 0.0f);
	drawI2(CC);
	if (ndone == true && i2y < 0.0f)
		i2y = i2y + 0.001f;
	if(i2y > 0.0f)
		i2done = true;
//A
	glLoadIdentity();
	glTranslatef(ax, 0.0f, -2.5f);
	glScalef(1.3f, 1.2f, 0.0f);
	drawA(CC);
	if (i2done == true && ax > 0.0f)
		ax = ax - 0.001f;
	if (ax < 0.0f)
		adone = true;

//Plane Animation
	if (ddone == true)
	{
		glLoadIdentity();
		glTranslatef(tx1, ty1,-2.5f);
		glScalef(1.3f, 1.2f, 0.0f);
		drawJet(one);
		drawSmoke(o);

		glLoadIdentity();
		glTranslatef(tx2, ty2, -2.5f);
		glScalef(1.3f, 1.2f, 0.0f);
		drawJet(two);
		drawSmoke(w);

		glLoadIdentity();
		glTranslatef(tx3, ty3, -2.5f);
		glScalef(1.3f, 1.2f, 0.0f);
		drawJet(three);
		drawSmoke(g);
		if (ty1 < -0.5f || ty3 > 0.5f)
		{
			p1 = true;
		}
		if (p1 != true)
		{
			tx1 = tx1 + speed;
			ty1 = ty1 - speed;

			tx2 = tx2 + speed;

			tx3 = tx3 + speed;
			ty3 = ty3 + speed;
		}
		if (tx1 > 1.8f)//1.7f
			p2 = true;

		if (p1 == true && p2 == false)
		{
			tx1 = tx1 + speed;
			tx2 = tx2 + speed;
			tx3 = tx3 + speed;
		}

		if (p1 == true && p2 == true && p3 == false)
		{
			tx1 = tx1 + speed;
			tx2 = tx2 + speed;
			ty1 = ty1 + speed;

			tx3 = tx3 + speed;
			ty3 = ty3 - speed;
		}
	}
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
		//speed = 0.001f;
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
		//speed = 0.001f;
		SetWindowLong(ghwnd, GWL_STYLE, dwstyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
		ShowCursor(TRUE);
		bFullScreen = false;
	}
}

void drawI(bool cc)
{
	//-0.4 to 0.5 range
	struct india t;
	t.Top = 0.3f;
	t.Bottom = -0.3f;
	t.Mid = 0.0f;
	t.left = 0.1f;
	//I
	glBegin(GL_POLYGON);
	if (cc == false)
	{
		WW
	}
	else
	{
		O
	}
	glVertex3f(-0.35f - t.left, t.Top, 0.0f);
	glVertex3f(-0.4f - t.left, t.Top, 0.0f);
	if (cc == false)
		W
	else
	GG
	glVertex3f(-0.4f - t.left, t.Bottom, 0.0f);
	glVertex3f(-0.35f - t.left, t.Bottom, 0.0f);
	glEnd();

	
	
}

void drawN(bool cc)
{
	//-0.4 to 0.5 range
	struct india t;
	t.Top = 0.3f;
	t.Bottom = -0.3f;
	t.Mid = 0.0f;
	t.left = 0.1f;

	//NLEFT
	glBegin(GL_QUADS);
	if (cc == false)
		W
	else
		OO
		glVertex3f(-0.25f - t.left, t.Top, 0.0f);
	glVertex3f(-0.30f - t.left, t.Top, 0.0f);
	if (cc == false)
		W
	else
		GG
		glVertex3f(-0.30f - t.left, t.Bottom, 0.0f);
	glVertex3f(-0.25f - t.left, t.Bottom, 0.0f);
	//---------\\  **/NMIDDLE
	if (cc == false)
		W
	else
		GG
		glVertex3f(-0.15f - t.left, t.Bottom, 0.0f);
	glVertex3f(-0.10f - t.left, t.Bottom, 0.0f);

	if (cc == false)
		W
	else
		OO
		glVertex3f(-0.25f - t.left, t.Top, 0.0f);
	glVertex3f(-0.30f - t.left, t.Top, 0.0f);
	//NRIGHT
	if (cc == false)
		W
	else
		OO
		glVertex3f(-0.10f - t.left, t.Top, 0.0f);
	glVertex3f(-0.15f - t.left, t.Top, 0.0f);
	if (cc == false)
		W
	else
		GG
		glVertex3f(-0.15f - t.left, t.Bottom, 0.0f);
	glVertex3f(-0.10f - t.left, t.Bottom, 0.0f);
	glEnd();

}

void drawD(bool cc ,bool anime,GLfloat CV)
{
	//-0.4 to 0.5 range
	struct india t;
	t.Top = 0.3f;
	t.Bottom = -0.3f;
	t.Mid = 0.0f;
	t.left = 0.1f;

	//D
	glBegin(GL_QUADS);
	//DTOP
	if (cc == false)
		CVD
	else
		OO
		glVertex3f(0.1f - t.left, t.Top, 0.0f);
	glVertex3f(0.0f - t.left, t.Top, 0.0f);
	glVertex3f(0.0f - t.left, t.Top - 0.05f, 0.0f);
	glVertex3f(0.1f - t.left, t.Top - 0.05f, 0.0f);
	if (cc == false)
		CVD
	else
		GG
		//DBOTTOM
		glVertex3f(0.1f - t.left, t.Bottom + 0.05f, 0.0f);
	glVertex3f(0.0f - t.left, t.Bottom + 0.05f, 0.0f);
	glVertex3f(0.0f - t.left, t.Bottom, 0.0f);
	glVertex3f(0.1f - t.left, t.Bottom, 0.0f);

	//DLEFT
	if (cc == false)
		CVD
	else
		OO
		glVertex3f(0.0f - t.left, t.Top, 0.0f);
	glVertex3f(-0.05f - t.left, t.Top, 0.0f);
	if (cc == false)
		CVD
	else
		GG
		glVertex3f(-0.05f - t.left, t.Bottom, 0.0f);
	glVertex3f(-0.0f - t.left, t.Bottom, 0.0f);
	//DRIGHT
	if (cc == false)
		CVD
	else
		OO
		glVertex3f(0.15f - t.left, t.Top - 0.05f, 0.0f);
	glVertex3f(0.1f - t.left, t.Top, 0.0f);
	if (cc == false)
		CVD
	else
		GG
		glVertex3f(0.1f - t.left, t.Bottom, 0.0f);
	glVertex3f(0.15f - t.left, t.Bottom + 0.05f, 0.0f);
	glEnd();
}

void drawI2(bool cc)
{
	//-0.4 to 0.5 range
	struct india t;
	t.Top = 0.3f;
	t.Bottom = -0.3f;
	t.Mid = 0.0f;
	t.left = 0.1f;

	glBegin(GL_QUADS);
	//I
	if (cc == false)
		W
	else
		OO
		glVertex3f(0.25f - t.left, t.Top, 0.0f);
	glVertex3f(0.2f - t.left, t.Top, 0.0f);
	if (cc == false)
		W
	else
		GG
		glVertex3f(0.2f - t.left, t.Bottom, 0.0f);
	glVertex3f(0.25f - t.left, t.Bottom, 0.0f);
	glEnd();

}

void drawA(bool cc)
{
	//-0.4 to 0.5 range
	struct india t;
	t.Top = 0.3f;
	t.Bottom = -0.3f;
	t.Mid = 0.0f;
	t.left = 0.1f;


	glBegin(GL_QUADS);
	//ALeft
	if (cc == false)
		W
	else
		OO
	glVertex3f(0.30f - t.left, t.Top - 0.05f, 0.0f);
	glVertex3f(0.35f - t.left, t.Top, 0.0f);
	if (cc == false)
		W
	else
		GG
	glVertex3f(0.35f - t.left, t.Bottom , 0.0f);
	glVertex3f(0.30f - t.left, t.Bottom + 0.05f, 0.0f);
	//ARight
	if (cc == false)
		W
	else
		OO
	glVertex3f(0.50f - t.left, t.Top - 0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Top, 0.0f);
	if (cc == false)
		W
	else
		GG
	glVertex3f(0.45f - t.left, t.Bottom, 0.0f);
	glVertex3f(0.50f - t.left, t.Bottom + 0.05f, 0.0f); // bottom - 
	//ATop
	if (cc == false)
		W
	else
		OO
	glVertex3f(0.45f - t.left, t.Top, 0.0f);
	glVertex3f(0.35f - t.left, t.Top, 0.0f);
	glVertex3f(0.35f - t.left, t.Top - 0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Top - 0.05f, 0.0f);

	//ATriFlag
	//O
	if (cc == false)
		W
	else
		OO

	glVertex3f(0.45f - t.left, t.Mid + 0.15f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid + 0.15f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid + 0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Mid + 0.05f, 0.0f);

	//W
	if (cc == false)
		W
	else
		WW

	glVertex3f(0.45f - t.left, t.Mid + 0.05f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid + 0.05f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid - 0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Mid - 0.05f, 0.0f);
	//G
	if (cc == false)
		W
	else
		GG

	glVertex3f(0.45f - t.left, t.Mid - 0.15f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid - 0.15f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid - 0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Mid - 0.05f, 0.0f);

	glEnd();
}


void drawJet(struct jet j)
{

	glBegin(GL_POLYGON);
	W
	//Body
	glVertex3f(j.right,j.mid, 0.0f);//1
	glVertex3f(j.right -0.05f ,j.mid+0.05f, 0.0f);//2
	glVertex3f(j.left - 0.03f,j.mid +0.05f, 0.0f);//3
	glVertex3f(j.left - 0.03f,j.mid -0.05f, 0.0f);//4
	glVertex3f(j.right - 0.05f,j.mid -0.05f, 0.0f);//5
	glVertex3f(j.right, j.mid, 0.0f);//1
	glEnd();

	//Tail
	glBegin(GL_QUADS);
	GGG
	glVertex3f(j.left - 0.06f + 0.04f, j.top + 0.02f, 0.0f);
	glVertex3f(j.left - 0.06f + 0.00f, j.top +0.02f,0.0f );
	glVertex3f(j.left - 0.03f + 0.00f, j.mid+ 0.05f,0.0f);
	glVertex3f(j.left - 0.03f + 0.06f, j.mid + 0.05f, 0.0f);

	glEnd();

	//Booster
	glBegin(GL_QUADS);
	O
	glVertex3f(j.left - 0.03f , j.mid + 0.02f, 0.0f);
	glVertex3f(j.left - 0.03f - 0.03f, j.mid + 0.05f, 0.0f);
	glVertex3f(j.left - 0.03f - 0.03f, j.mid - 0.05f, 0.0f);
	glVertex3f(j.left - 0.03f , j.mid - 0.02f, 0.0f);
	
	glEnd();

	glBegin(GL_QUADS);
	GR
	glVertex3f(j.wmid - 0.03f + 0.13f, j.mid - 0.05f , 0.0f);
	glVertex3f(j.wmid - 0.03f, j.mid , 0.0f);
	glVertex3f(j.wmid - 0.03f - 0.2f, j.mid - 0.05f , 0.0f);
	glVertex3f(j.wmid - 0.03f - 0.02f, j.bottom , 0.0f);
	glEnd();

}

void drawSmoke(struct smk s)
{
	glBegin(GL_QUADS);
	glColor3f(s.R,s.G,s.B);
	glVertex3f(s.right,s.top,0.0f);
	glVertex3f(s.left, s.top, 0.0f);
	glVertex3f(s.left, s.bottom, 0.0f);
	glVertex3f(s.right, s.bottom, 0.0f);
	glEnd();
}