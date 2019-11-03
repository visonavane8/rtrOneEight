
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define _USE_MATH_DEFINES 1
#include <math.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

using namespace std;

bool bFullscreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpXVisualInfo = NULL;
Colormap gColormap;
Window gWindow;
int giWindowWidth = 800;
int giWindowHeight = 600;

GLXContext gGLXContext;

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

//India 
void drawI(bool );
void drawN(bool );
void drawD(bool ,bool ,GLfloat);
void drawI2(bool );
void drawA(bool );
void drawJet(struct jet);
void drawSmoke(struct smk);
GLfloat speed = 0.001f;

void resize(int, int);
void update(void);
void drawTriangle();
void drawCircle();
void drawLine();

int main(void)
{
	
	void CreateWindow(void);
	void ToggleFullscreen(void);
	void uninitialize();
	void initialize(void);
	
	void display(void);

    
	int winWidth = giWindowWidth;
	int winHeight = giWindowHeight;
	char keys[26];
	bool bDone = false;

	XEvent event;
	KeySym keysym;
	
    CreateWindow();

    initialize();
	
    while(bDone == false)
    {
        while(XPending(gpDisplay))
        {
        	XNextEvent(gpDisplay, &event);
			switch(event.type)
			{
				case MapNotify:
					break;
				case KeyPress:
					keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
					switch(keysym)
					{
						case XK_Escape:
							bDone = true;					
						default:
							break;
					}
					XLookupString(&event.xkey,keys, sizeof(keys), NULL, NULL);
					switch(keys[0])
					{
						case 'f':
							if(bFullscreen == false)
							{
								ToggleFullscreen();
								bFullscreen = true;
							}
							else
							{
								ToggleFullscreen();
								bFullscreen = false;
							}
							break;
					}
					break;
				case ButtonPress:
					switch(event.xbutton.button)
					{
						case 1:		
							break;
						case 2:		
							break;
						case 3:		
							break;
						case 4:		
							break;
						case 5:		
							break;
						default:
							break;
					}
					break;
				case MotionNotify:		
					break;
				case ConfigureNotify:	
					winWidth = event.xconfigure.width;
					winHeight = event.xconfigure.height;
					resize(winWidth, winHeight);
					break;
				case Expose:			
					break;
				case DestroyNotify:		
					break;
				case 33:				
					bDone = true;
				default:
					break;
			}
        }
        update();
        display();
	}
	
	uninitialize();
	return(0);
}

void CreateWindow(void)
{
	
	void uninitialize(void);
	
    XSetWindowAttributes winAttribs;
    int defaultScreen;
    int styleMask;
    static int frameBufferAttributes[] = {
    	GLX_RGBA,
    	GLX_DOUBLEBUFFER, True,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        None
    };
	
    gpDisplay = XOpenDisplay(NULL);
    if(gpDisplay == NULL)
    {
        printf("Error: Unable to open XDisplay.\nExitting Now...\n");
        uninitialize();
        exit(1);
    }

    defaultScreen = XDefaultScreen(gpDisplay);
	
    gpXVisualInfo = glXChooseVisual(gpDisplay, defaultScreen, frameBufferAttributes);
    if(gpXVisualInfo == NULL)
    {
        printf("Error: Unable to choose visual.\nExitting Now...\n");
        uninitialize();
        exit(1);
    }

    winAttribs.border_pixel = 0;
    winAttribs.border_pixmap = 0;
    winAttribs.background_pixel = BlackPixel(gpDisplay, defaultScreen);
    winAttribs.background_pixmap = 0;
    winAttribs.colormap = XCreateColormap(gpDisplay, XRootWindow(gpDisplay, gpXVisualInfo->screen), gpXVisualInfo->visual, AllocNone);
    winAttribs.event_mask = ExposureMask | VisibilityChangeMask | ButtonPressMask | KeyPressMask | PointerMotionMask | StructureNotifyMask;

    styleMask = CWBorderPixel | CWBackPixel | CWEventMask | CWColormap;
    gColormap = winAttribs.colormap;

    gWindow = XCreateWindow(gpDisplay, XRootWindow(gpDisplay, gpXVisualInfo->screen), 0, 0, giWindowWidth, giWindowHeight, 0, gpXVisualInfo->depth, InputOutput, gpXVisualInfo->visual, styleMask, &winAttribs);

    if(!gWindow)
    {
        printf("Error: Failed to create main window.\nExitting Now...\n");
        uninitialize();
        exit(1);
    }

    XStoreName(gpDisplay, gWindow, "XWindow | Vinit V. Sonavane");

    Atom windowManagerDelete = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(gpDisplay, gWindow, &windowManagerDelete, 1);
	
    XMapWindow(gpDisplay, gWindow);
}

void initialize(void)
{
	
	void uninitialize(void);

	gGLXContext = glXCreateContext(gpDisplay, gpXVisualInfo, NULL, GL_TRUE);
	glXMakeCurrent(gpDisplay, gWindow, gGLXContext);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    resize(giWindowWidth, giWindowHeight);
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
	{
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, GLfloat(width) / GLfloat(height), 0.1f, 100.0f);
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

	glXSwapBuffers(gpDisplay, gWindow);
}

void update(void)
{
	
}

void ToggleFullscreen(void)
{
	
    Atom wm_state;
    Atom fullscreen;
    XEvent xev = {0};

	
    wm_state = XInternAtom(gpDisplay, "_NET_WM_STATE", False);
    memset(&xev, 0, sizeof(xev));
	
    xev.type = ClientMessage;
    xev.xclient.window = gWindow;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = bFullscreen ? 0 : 1;
	
	fullscreen = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);
    xev.xclient.data.l[1] = fullscreen;

    XSendEvent(gpDisplay, XRootWindow(gpDisplay, gpXVisualInfo->screen), False, StructureNotifyMask, &xev);
}

void uninitialize(void)
{
	GLXContext currentGLXContext = glXGetCurrentContext();
	if(currentGLXContext != NULL && currentGLXContext == gGLXContext)
	{
		glXMakeCurrent(gpDisplay, 0, 0);
	}
	if(gGLXContext)
	{
		glXDestroyContext(gpDisplay, gGLXContext);
	}
    if(gWindow)
    {
        XDestroyWindow(gpDisplay, gWindow);
    }

    if(gColormap)
    {
        XFreeColormap(gpDisplay, gColormap);
    }

    if(gpXVisualInfo)
    {
        free(gpXVisualInfo);
        gpXVisualInfo = NULL;
    }

    if(gpDisplay)
    {
        XCloseDisplay(gpDisplay);
        gpDisplay = NULL;
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


