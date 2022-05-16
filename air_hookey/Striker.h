// Striker
#pragma once

#include <windows.h>
#include <gl/gl.h>
#include<math.h>
#include <iostream>

#include "GlColor4fRGB.h"
#include "CustomOpenGLUtils.h"
#include "CustomOpenGLRect.h"
#include "StrikerMoveAreaLimits.h"

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
	CustomOpenGLRect goal;
	StrikerMoveAreaLimits moveAreaLimits;
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
		float speed,
		CustomOpenGLRect &goal,
		StrikerMoveAreaLimits &moveAreaLimits
	) {
		this->positionX = positionX;
		this->positionY = positionY;
		this->radius = radius;
		this->velocityX = velocityX;
		this->velocityY = velocityY;
		this->glColor3fRGB = glColor3fRGB;
		this->speed = speed;
		this->goal = goal;
		this->moveAreaLimits = moveAreaLimits;
	}

	void draw() {
		goal.draw();
		this->glColor3fRGB.applyGLColor();
		drawFilledCircle(
			this->positionX,
			this->positionY,
			this->radius,
			360
		);
	}

	void update() {
		if (
			this->moveUp &&
			this->positionY + this->radius + this->velocityY < this->moveAreaLimits.north
			) this->positionY += this->velocityY;
		if (
			this->moveRight &&
			this->positionX + this->radius + this->velocityX <this->moveAreaLimits.east
			) this->positionX += this->velocityX;
		if (
			this->moveDown &&
			this->positionY - this->radius - this->velocityY >this->moveAreaLimits.south
			) this->positionY -= this->velocityY;
		if (
			this->moveLeft &&
			this->positionX - this->radius - this->velocityX > this->moveAreaLimits.west
			) this->positionX -= this->velocityX;
	}
};

