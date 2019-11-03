#include<GL/freeglut.h>

bool bIsFullScreen = false;
int main(int argc, char *argv[])
{
	// Function Declarations
	void initialize(void);
	void uninitialize(void);
	void reshape(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);

	//Code
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First OpenFL Program - Vinit Vijay Sonavane");

	initialize();
	//callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return(0);
}//Main


void initialize(void)
{
	//Code
	glClearColor(0.0f, 0.0f,0.0f,1.0f);
}

void uninitialize(void)
{
	//Code
}

void reshape(int width, int height)
{
	//Code
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void display(void)
{
	//Code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_TRIANGLES);

	//GL_TRIANGLES();
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();
	glFlush();
}//Display

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27: glutLeaveMainLoop();
				 break;
		case 'F':
		case 'f':
					if (bIsFullScreen == false)
					{
						glutFullScreen();
						bIsFullScreen = true;
					}
					else
					{
						glutLeaveFullScreen();
						bIsFullScreen = false;

					}
					break;

	}//switch
}//keyboard

void mouse(int button, int state, int x, int y)
{
	//Code
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
						   break;
	case GLUT_RIGHT_BUTTON:
						   glutLeaveMainLoop();
						   break;

	}
}

