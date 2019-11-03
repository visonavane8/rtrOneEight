
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
#define OO t.R = 1.0f;t.G = 0.4f;t.B = 0.0f;glColor3f(t.R, t.G, t.B);
#define WW t.R = 1.0f;t.G = 1.0f;t.B = 1.0f;glColor3f(t.R, t.G, t.B);
#define GG t.R = 0.0f;t.G = 1.0f;t.B = 0.0f;glColor3f(t.R, t.G, t.B);

void drawIndia();

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

void resize(int width, int height)
{
	 if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, GLfloat(width) / GLfloat(height), 0.1f, 100.0f);
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.5f);
	glScalef(1.3f, 1.2f, 0.0f);
	drawIndia();

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

void drawIndia()
{
	struct india t;
	t.Top = 0.3f;
	t.Bottom = -0.3f;
	t.Mid = 0.0f;
	t.left = 0.1f;
	//I
	glBegin(GL_POLYGON);

	t.R = 1.0f;
	t.G = 0.5f;
	t.B = 0.0f;
	glColor3f(t.R, t.G, t.B);
	glVertex3f(-0.35f - t.left,t.Top,0.0f);
	glVertex3f(-0.4f - t.left,t.Top,0.0f);

	/*t.R = 1.0f;
	t.G = 1.0f;
	t.B = 1.0f;
	glColor3f(t.R, t.G, t.B);*/

	t.R = 0.0f;
	t.G = 1.0f;
	t.B = 0.0f;
	glColor3f(t.R, t.G, t.B);
	glVertex3f(-0.4f - t.left,t.Bottom,0.0f);
	glVertex3f(-0.35f - t.left,t.Bottom,0.0f);
	glEnd();

	//NLEFT
	glBegin(GL_QUADS);
	OO
	glVertex3f(-0.25f - t.left, t.Top, 0.0f);
	glVertex3f(-0.30f - t.left, t.Top, 0.0f);
	GG
	glVertex3f(-0.30f - t.left, t.Bottom, 0.0f);
	glVertex3f(-0.25f - t.left, t.Bottom, 0.0f);
//---------\\  **/NMIDDLE
	
	GG
	glVertex3f(-0.15f - t.left, t.Bottom , 0.0f);
	glVertex3f(-0.10f - t.left, t.Bottom , 0.0f);
	OO
	glVertex3f(-0.25f - t.left, t.Top, 0.0f);
	glVertex3f(-0.30f - t.left, t.Top , 0.0f);
	//NRIGHT
	OO
	glVertex3f(-0.10f - t.left, t.Top, 0.0f);
	glVertex3f(-0.15f - t.left, t.Top, 0.0f);
	GG
	glVertex3f(-0.15f - t.left, t.Bottom, 0.0f);
	glVertex3f(-0.10f - t.left, t.Bottom, 0.0f);
	glEnd();

	//D
	glBegin(GL_QUADS);
	//DTOP
	OO
	glVertex3f(0.1f - t.left, t.Top, 0.0f);
	glVertex3f(0.0f - t.left, t.Top, 0.0f);
	glVertex3f(0.0f - t.left, t.Top-0.05f, 0.0f);
	glVertex3f(0.1f - t.left, t.Top-0.05f, 0.0f);

	GG
	//DBOTTOM
	glVertex3f(0.1f - t.left, t.Bottom+0.05f, 0.0f);
	glVertex3f(0.0f - t.left, t.Bottom+0.05f, 0.0f);
	glVertex3f(0.0f - t.left, t.Bottom, 0.0f);
	glVertex3f(0.1f - t.left, t.Bottom, 0.0f);

	//DLEFT
	OO
	glVertex3f(0.0f - t.left, t.Top, 0.0f);
	glVertex3f(-0.05f - t.left, t.Top, 0.0f);
	GG
	glVertex3f(-0.05f - t.left, t.Bottom, 0.0f);
	glVertex3f(-0.0f - t.left, t.Bottom, 0.0f);
	//DRIGHT
	OO
	glVertex3f(0.15f - t.left, t.Top-0.05f, 0.0f);
	glVertex3f(0.1f - t.left, t.Top, 0.0f);
	GG
	glVertex3f(0.1f - t.left, t.Bottom, 0.0f);
	glVertex3f(0.15f - t.left, t.Bottom+0.05f, 0.0f);

	//I
	OO
	glVertex3f(0.25f - t.left, t.Top, 0.0f);
	glVertex3f(0.2f - t.left, t.Top, 0.0f);
	GG
	glVertex3f(0.2f - t.left, t.Bottom, 0.0f);
	glVertex3f(0.25f - t.left, t.Bottom, 0.0f);

	//ALeft
	OO
	glVertex3f(0.30f - t.left, t.Top-0.05f, 0.0f);
	glVertex3f(0.35f - t.left, t.Top, 0.0f);
	GG
	glVertex3f(0.35f - t.left, t.Bottom, 0.0f);
	glVertex3f(0.30f - t.left, t.Bottom+0.05f, 0.0f);
	//ARight
	OO
	glVertex3f(0.50f - t.left, t.Top-0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Top, 0.0f);
	GG
	glVertex3f(0.45f - t.left, t.Bottom, 0.0f);
	glVertex3f(0.50f - t.left, t.Bottom-0.05f, 0.0f);
	//ATop
	
	OO
	glVertex3f(0.45f - t.left, t.Top, 0.0f);
	glVertex3f(0.35f - t.left, t.Top, 0.0f);
	glVertex3f(0.35f - t.left, t.Top-0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Top-0.05f, 0.0f);
	
	//ATriFlag
	//O
	OO

	glVertex3f(0.45f - t.left, t.Mid + 0.15f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid + 0.15f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid + 0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Mid + 0.05f, 0.0f);
	//W
	WW

	glVertex3f(0.45f - t.left, t.Mid + 0.05f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid + 0.05f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid - 0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Mid - 0.05f, 0.0f);
	//G
	GG

	glVertex3f(0.45f - t.left, t.Mid - 0.15f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid - 0.15f, 0.0f);
	glVertex3f(0.35f - t.left, t.Mid - 0.05f, 0.0f);
	glVertex3f(0.45f - t.left, t.Mid - 0.05f, 0.0f);
	
	
	glEnd();
}


