#include<GL/freeglut.h>
#include<GL/GLU.h>

#pragma comment(lib,"glu32.lib")

#define R glColor3f(1.0f,0.0f,0.0f);
#define G glColor3f(0.0f,1.0f,0.0f);
#define B glColor3f(0.0f,0.0f,1.0f);

void drawTriangle();
void drawCube();

bool bIsFullScreen = false;
GLfloat angle = 0.0f;
GLfloat step = 0.1f;
int refresh = 1;
int year = 0, day = 0;

int main(int argc, char *argv[])
{
	// Function Declarations
	void initialize(void);
	void uninitialize(void);
	void reshape(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void Update();
	void timer(int);

	//Code
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA );
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My Second GLUT Program - Vinit Vijay Sonavane");

	initialize();
	//callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);
	glutIdleFunc(Update);
	//glutTimerFunc(0, timer, 0);
	glutMainLoop();
	

	return(0);
}//Main

void timer(int value) {
	      // Post re-paint request to activate display()
	glutTimerFunc(refresh, timer, 0); // next timer call milliseconds later
}

void initialize(void)
{
	//Code
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f); //Step 2
	glEnable(GL_DEPTH_TEST);  //Step 4
	glDepthFunc(GL_LEQUAL);   //Step 5
}

void uninitialize(void)
{
	//Code
}

void reshape(int width, int height)
{
	//Code
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);
}


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
	case 'Y':
		year = (year + 5) % 360; glutPostRedisplay(); break;
	case 'y':
		year = (year - 5) % 360; glutPostRedisplay(); break;
	case 'D':
		day = (day + 10) % 360;  glutPostRedisplay(); break;
	case 'd':
		day = (day - 10) % 360;  glutPostRedisplay(); break;
	case VK_SPACE:
		step = step + step;
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

void display(void)
{
	//Codegl
	        
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Step 3
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	
	glutWireSphere(1.0f, 20.0f, 16.0f);
	glRotatef((GLfloat)year, 0.0f, 1.0f, 0.0f);
	glTranslatef(2.0f,0.0f,0.0f);
	glRotatef((GLfloat)day,  0.0f,1.0f , 0.0f);
	glutWireSphere(0.2f, 10.0f, 8.0f);
	glPopMatrix();
	/*glTranslatef(-1.5f, 0.0f, -7.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	drawTriangle();

	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -7.0f);
	glScalef(0.75f, 0.75f, 0.75f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);

	drawCube();
	*/
	glutPostRedisplay();
	glutSwapBuffers();
	
	
}//Display



void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	R
		glVertex3f(0.0f, 1.0f, 0.0f);
	G
		glVertex3f(-1.0f, -1.0f, 1.0f);
	B
		glVertex3f(1.0f, -1.0f, 1.0f);

	R
		glVertex3f(0.0f, 1.0f, 0.0f);
	B
		glVertex3f(1.0f, -1.0f, 1.0f);
	G
		glVertex3f(1.0f, -1.0f, -1.0f);

	R
		glVertex3f(0.0f, 1.0f, 0.0f);
	G
		glVertex3f(1.0f, -1.0f, -1.0f);
	B
		glVertex3f(-1.0f, -1.0f, -1.0f);

	R
		glVertex3f(0.0f, 1.0f, 0.0f);
	B
		glVertex3f(-1.0f, -1.0f, -1.0f);
	G
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
}

void Update()
{
	if (angle > 360.0f)
		angle = 0.0f;

	angle += step;
}

void drawCube() {

	glBegin(GL_QUADS);
	//Top
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	//Bottom
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	//Front
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	//Back
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	//Right
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	//Left
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();


}