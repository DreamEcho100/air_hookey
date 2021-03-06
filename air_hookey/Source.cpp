#include <string>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
//
#include<math.h>
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
#include "CustomOpenGlText.h"


//using namespace std;

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

int player1Score = 0;
int player2Score = 0;
CustomOpenGlText *playerScoresTextHandler;
std::string playersScoresText;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

std::string buildPlayersScoresText();

void InitGraphics(int argc, char* argv[]);

void SetTransformations();

void calcFramePerSecond();

void onKeyPress(unsigned char key, int x, int y);
void onKeyUp(unsigned char key, int x, int y);

void onSpecialKeyPress(int key, int x, int y);
void onSpecialKeyUp(int key, int x, int y);

void OnDisplay();

void drawCoordinate();
void initBackground();
void initPlayer1();
void initPlayer2();
void initPuck();

std::string buildPlayersScoresText() {
	return "player 1 = " + std::to_string(player1Score) + ", player 2 = " + std::to_string(player2Score);
}

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
	float borderY = canvasY - (canvasHeight * 0.1);
	float borderWidth = canvasWidth * 0.5;
	float borderHeight = canvasHeight * 0.8;
	//
	playerScoresTextHandler = new CustomOpenGlText(
		new Vector(0, 0),
		new GlColor4fRGB(1.0f, 1.0f, 1.0f, 1.0f),
		GLUT_BITMAP_8_BY_13,
		buildPlayersScoresText()
	);
	//
	float fieldMarginX = abs(borderX * 0.1);
	float fieldMarginY = abs(borderX * 0.1);

	float fieldX = borderX + fieldMarginX;
	float fieldY = borderY - fieldMarginY;
	float fieldWidth = borderWidth - (fieldMarginX * 2);
	float fieldHeight = borderHeight - (fieldMarginY * 2);

	CustomOpenGLRect* background = new CustomOpenGLRect(
		new Vector(canvasX, canvasY),
		canvasWidth,
		canvasHeight,
		*new GlColor4fRGB(0.0f, 0.0f, 0.0f, 1.0f)
	);

	CustomOpenGLRect* border = new CustomOpenGLRect(
		new Vector(borderX, borderY),
		borderWidth,
		borderHeight,
		*new GlColor4fRGB(1.0f, 0.0f, 0.0f, 1.0f)
	);
	CustomOpenGLRect* field = new CustomOpenGLRect(
		new Vector(fieldX, fieldY),
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
	float goalPositionY = -playLayout->field->position->y + 40;
	player1 = new Striker(
		new Vector(0, -playLayout->field->position->y + 75 + 50),
		75.0f,
		new Vector(0, 0),
		new Vector(0, 0),
		new GlColor4fRGB(0.5f, 0.0f, 1.0f, 1.0f),
		new StrikerMoveAreaLimits(
			playLayout->field->position->y - (playLayout->field->height / 2),
			playLayout->field->position->x + playLayout->field->width,
			goalPositionY,
			playLayout->field->position->x
		),
		//
		new CustomOpenGLRect(
			new Vector(0 - 125, goalPositionY),
			250,
			40,
			*new GlColor4fRGB(0.0f, 0.0f, 0.0f, 1.0f)
		)
	);
}
void initPlayer2() {
	float goalPositionY = playLayout->field->position->y;
	float goalHeight = 40;
	player2 = new Striker(
		new Vector(0, playLayout->field->position->y - 75 - 50),
		75,
		new Vector(0, 0),
		new Vector(0, 0),
		new GlColor4fRGB(.0f, 0.0f, 0.5f, 1.0f),
		new StrikerMoveAreaLimits(
			goalPositionY - goalHeight,
			playLayout->field->position->x + playLayout->field->width,
			playLayout->field->position->y - (playLayout->field->height / 2),
			playLayout->field->position->x
		),
		//
		new CustomOpenGLRect(
			new Vector(0 - 125, goalPositionY),
			250,
			goalHeight,
			*new GlColor4fRGB(0.0f, 0.0f, 0.0f, 1.0f)
		)
	);
}
void initPuck() {
	//Striker* players[2] = { player1 , player2 };

	puck = new Puck(
		new Vector(playLayout->field->position->x + (playLayout->field->width / 2), playLayout->field->position->y - (playLayout->field->height / 2)), // (0, 0)
		50,
		new Vector(0, 0),
		new Vector(0, 0),
		new GlColor4fRGB(0.0f, 0.5f, 0.0f, 1.0f),
		new StrikerMoveAreaLimits(
			playLayout->field->position->y,
			playLayout->field->position->x + playLayout->field->width,
			playLayout->field->position->y - playLayout->field->height,
			playLayout->field->position->x
		),
		player1,
		player2
	);
}

void resetingPositions() {
	initPlayer1();
	initPlayer2();
	initPuck();
}

void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(0, 0); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(playLayout->windowWidth, playLayout->windowHeight);
	glutCreateWindow("air_hookey");
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
		//cout << frameCounter << endl;
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
	float xAxis = (playLayout->background->width * 0.5);
	float yAxis = (playLayout->background->height * 0.5);
	gluOrtho2D(-xAxis, xAxis, -yAxis, yAxis);
}

void OnDisplay() {
	//set the background color to white
	glClearColor(1, 1, 1, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT);

	SetTransformations();

	playLayout->draw();

	drawCoordinate();

	player1->draw();
	player1->goal-> draw();
	player2->draw();
	player2->goal->draw();
	puck->draw();
	playerScoresTextHandler->draw();
	glFlush();

	glutSwapBuffers();

	if (updateFrame) {
		player1->update();
		player2->update();
		puck->update();

		bool isResetingPositions = false;
		if (puck->hasRectIntersection(player1->goal)) {
			player2Score += 1;
			playerScoresTextHandler->str = buildPlayersScoresText();
			isResetingPositions = true;
		}
		if (puck->hasRectIntersection(player2->goal)) {
			player1Score += 1;
			playerScoresTextHandler->str = buildPlayersScoresText();
			isResetingPositions = true;
		}
		if (isResetingPositions) resetingPositions();
	}

	glutPostRedisplay();
}

void drawCoordinate() {
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	// X-axis
	glVertex2f(playLayout->background->position->x, 0);
	glVertex2f(playLayout->background->position->x + playLayout->background->height, 0);
	glColor3f(0, 0, 1);
	// Y-axis
	glVertex2f(0, playLayout->background->position->y);
	glVertex2f(0, playLayout->background->position->y - playLayout->background->height);
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
		player1->velocity->x = 0;
		break;
	}
	case 'd':
	case 'D': {
		player2->moveRight = false;
		player1->velocity->x = 0;
		break;
	}
	case 'w':
	case 'W': {
		player2->moveUp = false;
		player1->velocity->y = 0;
		break;
	}
	case 's':
	case 'S': {
		player2->moveDown = false;
		player1->velocity->y = 0;
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
		player1->velocity->x = 0;
		break;
	}
	case GLUT_KEY_RIGHT: {
		player1->moveRight = false;
		player1->velocity->x = 0;
		break;
	}
	case GLUT_KEY_UP: {
		player1->moveUp = false;
		player1->velocity->y = 0;
		break;
	}
	case GLUT_KEY_DOWN: {
		player1->velocity->y = 0;
		player1->moveDown = false;
		break;
	}

	default:
		break;
	}
};
