#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include<math.h>
#include "Striker.h"

float topEdgeX = 15;
float leftEdgeX = 0;
float rightEdgeX = 30;
float vx = 0.05;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

void InitGraphics(int argc, char* argv[]);

void SetTransformations();

void OnDisplay();

void Draw_Coordinate();

int main(int argc, char* argv[]) {
	InitGraphics(argc, argv);

	Striker *player1 = new Striker(
		0,
		-1000,
		1,
		1,
		10,
		*new GlColor4fRGB(0.5f, 0.0f, 1.0f, 1.0f),
		10
	);

	return 0;
}

void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(500, 50); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Air Hokey");
	//OnDisplay will handle the paint event
	glutDisplayFunc(OnDisplay);
	//	glutIdleFunc(OnDisplay);
	//SetTransformations();
	// to keep the window open 
	glutMainLoop();
}

void SetTransformations() {
	//set up the logical coordinate system of the window: [-100, 100] x [-100, 100]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
}

void OnDisplay() {
	//set the background color to white
	glClearColor(1, 1, 1, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT);

	SetTransformations();

	Draw_Coordinate();

	glTranslated(0, 0, 0);
	glScalef(1, 1, 1);
	glRotatef(0, 0, 0, 0);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(rightEdgeX, 0);
	glColor3f(0, 1, 0);
	glVertex2f(topEdgeX, 30);
	glColor3f(0, 0, 1);
	glVertex2f(leftEdgeX, 0);
	glEnd();

	glFlush();

	glutSwapBuffers();

	if (rightEdgeX + vx >= 100 || leftEdgeX + vx <= -100) vx *= -1;

	topEdgeX += vx;
	leftEdgeX += vx;
	rightEdgeX += vx;


	glutPostRedisplay();
}

void Draw_Coordinate() {
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	// X-axis
	glVertex2f(-100, 0);
	glVertex2f(100, 0);
	glColor3f(0, 0, 1);
	// Y-axis
	glVertex2f(0, -100);
	glVertex2f(0, 100);
	glEnd();
}
