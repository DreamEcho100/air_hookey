#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include<math.h>
#include "PlayLayout.h"
#include "Striker.h"
#include <iostream>

float topEdgeX = 15;
float leftEdgeX = 0;
float rightEdgeX = 30;
float vx = 0.05;

PlayLayout *playLayout;
Striker* player1;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

void InitGraphics(int argc, char* argv[]);

void SetTransformations();

void OnDisplay();

void Draw_Cordinat();

int main(int argc, char* argv[]) {
	float canvasXAxis = 1000;
	float canvasYAxis = 1000;
	GlColor4fRGB canvasGlColor3fRGB = *new GlColor4fRGB(0.0f, 0.0f, 0.0f, 1.0f);
	float borderY = canvasXAxis * 0.99;
	float borderX = canvasYAxis * 0.5;
	GlColor4fRGB borderGlColor3fRGB = *new GlColor4fRGB(1.0f, 0.0f, 0.0f, 1.0f);
	float fieldY = borderY - 30;
	float fieldX = borderX - 30;
	GlColor4fRGB fieldGlColor3fRGB = *new GlColor4fRGB(1.0f, 1.0f, 1.0f, 1.0f);
	playLayout = new PlayLayout(
		canvasXAxis,
		canvasYAxis,
		canvasGlColor3fRGB,
		borderX,
		borderY,
		borderGlColor3fRGB,
		fieldX,
		fieldY,
		fieldGlColor3fRGB
	);

	player1 = new Striker(
		0,
		-fieldY + 50 + 40,
		50,
		1,
		1,
		*new GlColor4fRGB(0.5f, 0.0f, 1.0f, 1.0f),
		10
	);

	InitGraphics(argc, argv);
	return 0;
}

void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(0, 0); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(playLayout->canvasYAxis, playLayout->canvasYAxis);
	glutCreateWindow("OpenGL Lab");
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
	gluOrtho2D(-playLayout->canvasXAxis, playLayout->canvasXAxis, -playLayout->canvasYAxis, playLayout->canvasYAxis);
}

void OnDisplay() {
	//set the background color to white
	glClearColor(1, 1, 1, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT);

	SetTransformations();

	playLayout->draw();
	Draw_Cordinat();

	player1->draw();

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

	if (rightEdgeX + vx >= playLayout->canvasXAxis || leftEdgeX + vx <= -playLayout->canvasXAxis) vx *= -1;

	topEdgeX += vx;
	leftEdgeX += vx;
	rightEdgeX += vx;


	glutPostRedisplay();
}

void Draw_Cordinat() {
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	// X-axis
	glVertex2f(-playLayout->canvasXAxis, 0);
	glVertex2f(playLayout->canvasXAxis, 0);
	glColor3f(0, 0, 1);
	// Y-axis
	glVertex2f(0, -playLayout->canvasYAxis);
	glVertex2f(0, playLayout->canvasYAxis);
	glEnd();
}
