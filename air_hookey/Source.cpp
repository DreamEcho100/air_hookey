#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
//
#include<math.h>
#include <iostream>
//
#include<synchapi.h>
//
#include <ctime>
#include <cstdio>
//
#include "PlayLayout.h"
#include "Vector.h"
#include "Striker.h"
#include "Puck.h"
#include "CustomOpenGLRect.h"
#include "StrikerMoveAreaLimits.h"


using namespace std;

UINT prevFrameTime = -1;
UINT currentFrameTime = -1;
UINT frameCounter = 0;

float topEdgeX = 15;
float leftEdgeX = 0;
float rightEdgeX = 30;
float vx = 0.05;

boolean updateFrame = true;

PlayLayout* playLayout;
Striker* player1;
Striker* player2;
Puck* puck;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

void InitGraphics(int argc, char* argv[]);

void SetTransformations();

void calcFramePerSecond();

void onKeyPress(unsigned char key, int x, int y);
void onKeyUp(unsigned char key, int x, int y);

void onSpecialKeyPress(int key, int x, int y);
void onSpecialKeyUp(int key, int x, int y);

void OnDisplay();

void drawCordinate();
void initBackground();
void initPlayer1();
void initPlayer2();
void initPuck();
//Puck* puck;

int main(int argc, char* argv[]) {
	initBackground();
	initPlayer1();
	initPlayer2();
	initPuck();

	InitGraphics(argc, argv);
	return 0;
}

void initBackground() {
	int windowWidth = 1000;
	int windowHeight = 1000;
	//
	float canvasX = -1000;
	float canvasY = 1000;
	float canvasWidth = 2000;
	float canvasHeight = 2000;
	//
	float borderX = canvasX + (canvasWidth * 0.25);
	float borderY = canvasY - (canvasHeight * 0.025);
	float borderWidth = canvasWidth * 0.5;
	float borderHeight = canvasHeight * 0.95;
	//
	float fieldMarginX = abs(borderX * 0.05);
	float fieldMarginY = abs(borderX * 0.05);

	float fieldX = borderX + fieldMarginX;
	float fieldY = borderY - fieldMarginY;
	float fieldWidth = borderWidth - (fieldMarginX * 2);
	float fieldHeight = borderHeight - (fieldMarginY * 2);

	CustomOpenGLRect background = *new CustomOpenGLRect(
		canvasX,
		canvasY,
		canvasWidth,
		canvasHeight,
		*new GlColor4fRGB(0.0f, 0.0f, 0.0f, 1.0f)
	);

	CustomOpenGLRect border = *new CustomOpenGLRect(
		borderX,
		borderY,
		borderWidth,
		borderHeight,
		*new GlColor4fRGB(1.0f, 0.0f, 0.0f, 1.0f)
	);
	CustomOpenGLRect field = *new CustomOpenGLRect(
		fieldX,
		fieldY,
		fieldWidth,
		fieldHeight,
		*new GlColor4fRGB(1.0f, 1.0f, 1.0f, 1.0f)
	);

	playLayout = new PlayLayout(
		windowWidth,
		windowHeight,
		background,
		border,
		field
	);
}
void initPlayer1() {
	CustomOpenGLRect goal = *new CustomOpenGLRect(
		0 - 125,
		-playLayout->field.positionY + 40,
		250,
		40,
		*new GlColor4fRGB(0.0f, 0.0f, 0.0f, 1.0f)
	);
	Vector position = *new Vector(0, -playLayout->field.positionY + 75 + 50);
	player1 = new Striker(
		new Vector(0, -playLayout->field.positionY + 75 + 50),
		75,
		new Vector(4, 4),
		new Vector(4, 4),
		new Vector(1, 1),
		new GlColor4fRGB(0.5f, 0.0f, 1.0f, 1.0f),
		&goal,
		new StrikerMoveAreaLimits(
			playLayout->field.positionY - (playLayout->field.height / 2),
			playLayout->field.positionX + playLayout->field.width,
			goal.positionY,
			playLayout->field.positionX
		)
	);
}
void initPlayer2() {
	CustomOpenGLRect goal = *new CustomOpenGLRect(
		0 - 125,
		playLayout->field.positionY,
		250,
		40,
		*new GlColor4fRGB(0.0f, 0.0f, 0.0f, 1.0f)
	);
	player2 = new Striker(
		new Vector(0, playLayout->field.positionY - 75 - 50),
		75,
		new Vector(4, 4),
		new Vector(4, 4),
		new Vector(1, 1),
		new GlColor4fRGB(.0f, 0.0f, 0.5f, 1.0f),
		&goal,
		new StrikerMoveAreaLimits(
			goal.positionY - goal.height,
			playLayout->field.positionX + playLayout->field.width,
			playLayout->field.positionY - (playLayout->field.height / 2),
			playLayout->field.positionX
		)
	);
}
void initPuck() {
	//Striker* players[2] = { player1 , player2 };
	/*
		Vector *position,
		float radius,
		Vector *speed,
		Vector *velocity,
		Vector *acc,
		GlColor4fRGB *glColor3fRGB,
		StrikerMoveAreaLimits *moveAreaLimits,
		Striker *player1,
		Striker *player2
		*/

	puck = new Puck(
		new Vector(playLayout->field.positionX + (playLayout->field.width / 2), playLayout->field.positionY - (playLayout->field.height / 2)), // (0, 0)
		50,
		new Vector(320, 320),
		new Vector(320, 320),
		new Vector(1, 1),
		new GlColor4fRGB(0.0f, 0.5f, 0.0f, 1.0f),
		new StrikerMoveAreaLimits(
			playLayout->field.positionY,
			playLayout->field.positionX + playLayout->field.width,
			playLayout->field.positionY + playLayout->field.height,
			playLayout->field.positionX
		),
		player1,
		player2
		/*
		*new Vector(playLayout->field.positionX + (playLayout->field.width / 2), playLayout->field.positionY - (playLayout->field.height / 2)), // (0, 0)
		50,
		*new Vector(320, 320),
		*new Vector(320, 320),
		*new Vector(1, 1),
		*new GlColor4fRGB(0.0f, 0.5f, 0.0f, 1.0f),
		*new StrikerMoveAreaLimits(
			playLayout->field.positionY,
			playLayout->field.positionX + playLayout->field.width,
			playLayout->field.positionY + playLayout->field.height,
			playLayout->field.positionX
		)
		*/
	);
}

void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(0, 0); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(playLayout->windowWidth, playLayout->windowHeight);
	glutCreateWindow("OpenGL Lab");
	//OnDisplay will handle the paint event
	glutDisplayFunc(OnDisplay);

	glutKeyboardFunc(onKeyPress); // Tell GLUT to use the method "onKeyPress" for key presses 
	glutKeyboardUpFunc(onKeyUp); // Tell GLUT to use the method "onKeyUp" for key up events

	glutSpecialFunc(onSpecialKeyPress); // Tell GLUT to use the method "onSpecialKeyPress" for special key presses
	glutSpecialUpFunc(onSpecialKeyUp); // Tell GLUT to use the method "onSpecialKeyUp" for special up key events
	//	glutIdleFunc(OnDisplay);
	//SetTransformations();
	// to keep the window open 
	glutMainLoop();
}

void calcFramePerSecond()
{
	currentFrameTime = GetTickCount64();
	//the first update?
	if (prevFrameTime == -1) {
		prevFrameTime = currentFrameTime;
	}

	if (frameCounter < 60) {
		cout << frameCounter << endl;
		frameCounter += (currentFrameTime - prevFrameTime) / 1000.0;
		updateFrame = true;
		return;
	}


	frameCounter = 0;
	updateFrame = false;
	return;

}

void SetTransformations() {
	//set up the logical coordinate system of the window: [-100, 100] x [-100, 100]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float xAxis = (playLayout->background.width * 0.5);
	float yAxis = (playLayout->background.height * 0.5);
	gluOrtho2D(-xAxis, xAxis, -yAxis, yAxis);
}

void OnDisplay() {
	//set the background color to white
	glClearColor(1, 1, 1, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT);

	SetTransformations();

	playLayout->draw();

	drawCordinate();


	//glBegin(GL_QUADS);

	//glVertex2f(playLayout->fieldX);

	//glEnd();

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

	player1->draw();
	player2->draw();
	puck->draw();
	glFlush();


	glutSwapBuffers();

	if (updateFrame) {
		player1->update();
		player2->update();
		puck->update();

		if (rightEdgeX + vx > playLayout->background.positionX + playLayout->background.width || leftEdgeX + vx < playLayout->background.positionX) vx *= -1;

		topEdgeX += vx;
		leftEdgeX += vx;
		rightEdgeX += vx;
	}

	glutPostRedisplay();
}

void drawCordinate() {
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	// X-axis
	glVertex2f(playLayout->background.positionX, 0);
	glVertex2f(playLayout->background.positionX + playLayout->background.height, 0);
	glColor3f(0, 0, 1);
	// Y-axis
	glVertex2f(0, playLayout->background.positionY);
	glVertex2f(0, playLayout->background.positionY - playLayout->background.height);
	glEnd();
}

void onKeyPress(unsigned char key, int x, int y) {
	if (!updateFrame) return;

	switch (key)
	{
	case 'a':
	case 'A': {
		player2->moveLeft = true;
		break;
	}
	case 'd':
	case 'D': {
		player2->moveRight = true;
		break;
	}
	case 'w':
	case 'W': {
		player2->moveUp = true;
		break;
	}
	case 's':
	case 'S': {
		player2->moveDown = true;
		break;
	}

	default:
		break;
	}
};
void onKeyUp(unsigned char key, int x, int y) {
	if (!updateFrame) return;

	switch (key)
	{
	case 'a':
	case 'A': {
		player2->moveLeft = false;
		break;
	}
	case 'd':
	case 'D': {
		player2->moveRight = false;
		break;
	}
	case 'w':
	case 'W': {
		player2->moveUp = false;
		break;
	}
	case 's':
	case 'S': {
		player2->moveDown = false;
		break;
	}

	default:
		break;
	}
};

void onSpecialKeyPress(int key, int x, int y) {
	if (!updateFrame) return;

	switch (key)
	{
	case GLUT_KEY_LEFT: {
		player1->moveLeft = true;
		break;
	}
	case GLUT_KEY_RIGHT: {
		player1->moveRight = true;
		break;
	}
	case GLUT_KEY_UP: {
		player1->moveUp = true;
		break;
	}
	case GLUT_KEY_DOWN: {
		player1->moveDown = true;
		break;
	}

	default:
		break;
	}
};
void onSpecialKeyUp(int key, int x, int y) {
	if (!updateFrame) return;

	switch (key)
	{
	case GLUT_KEY_LEFT: {
		player1->moveLeft = false;
		break;
	}
	case GLUT_KEY_RIGHT: {
		player1->moveRight = false;
		break;
	}
	case GLUT_KEY_UP: {
		player1->moveUp = false;
		break;
	}
	case GLUT_KEY_DOWN: {
		player1->moveDown = false;
		break;
	}

	default:
		break;
	}
};
