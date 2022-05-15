// Striker
#pragma once

#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include<math.h>

#include "GlColor4fRGB.h"

using namespace std;

#define M_PI 3.14159265358979323846

class Striker
{
public:
	float positionX;
	float positionY;
	float radius;
	float velocityX;
	float velocityY;
	GlColor4fRGB glColor3fRGB;
	float speed;
	boolean moveRight = false;
	boolean moveLeft = false;
	boolean moveUp = false;
	boolean moveDown = false;

public:
	Striker() = default;
	Striker(
		float positionX,
		float positionY,
		float radius,
		float velocityX,
		float velocityY,
		GlColor4fRGB& glColor3fRGB,
		float speed
	) {
		this->positionX = positionX;
		this->positionY = positionY;
		this->radius = radius;
		this->velocityX = velocityX;
		this->velocityY = velocityY;
		this->glColor3fRGB = glColor3fRGB;
		this->speed = speed;
	}

	// https://stackoverflow.com/a/25423759/13961420
	void drawUnfilledCircle(float xi, float yj, float r1, int num1)
	{
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < num1; i++)
		{
			float theta = 2.0f * M_PI * float(i) / float(num1);
			float x1 = r1 * cosf(theta);
			float y1 = r1 * sinf(theta);
			glVertex2f(xi + x1, yj + y1);
		}
		glEnd();
	}

	void drawFilledCircle(float xi, float yj, float r1, int num1)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xi, yj);
		for (int i = 0; i <= num1; i++)
		{
			float theta = 2.0f * M_PI * float(i) / float(num1);
			float x1 = r1 * cosf(theta);
			float y1 = r1 * sinf(theta);
			glVertex2f(xi + x1, yj + y1);
		}
		glEnd();
	}


	void draw() {
		this->glColor3fRGB.applyGLColor();
		drawFilledCircle(
			this->positionX,
			this->positionY,
			this->radius,
			360
		);
	}

	void update() {}
};

