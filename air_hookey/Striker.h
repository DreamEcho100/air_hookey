// Striker
#pragma once

#include <windows.h>
#include <gl/gl.h>
#include<math.h>
#include <iostream>

#include "Vector.h"
#include "GlColor4fRGB.h"
#include "CustomOpenGLUtils.h"
#include "CustomOpenGLRect.h"
#include "StrikerMoveAreaLimits.h"

using namespace std;

#define M_PI 3.14159265358979323846

class Striker
{
public:
	Vector *position;
	float radius;
	Vector *speed;
	Vector *velocity;
	Vector *acc;
	GlColor4fRGB *glColor3fRGB;
	CustomOpenGLRect *goal;
	StrikerMoveAreaLimits *moveAreaLimits;
	//
	boolean moveRight = false;
	boolean moveLeft = false;
	boolean moveUp = false;
	boolean moveDown = false;

public:
	Striker() = default;
	Striker(
		Vector *position,
		float radius,
		Vector *speed,
		Vector *velocity,
		Vector *acc,
		GlColor4fRGB *glColor3fRGB,
		CustomOpenGLRect *goal,
		StrikerMoveAreaLimits *moveAreaLimits
	) {
		this->position = position;
		this->radius = radius;
		this->speed = speed;
		this->velocity = velocity;
		this->acc = acc;
		this->glColor3fRGB = glColor3fRGB;
		this->goal = goal;
		this->moveAreaLimits = moveAreaLimits;
	}

	void draw() {
		goal->draw();
		this->glColor3fRGB->applyGLColor();
		drawFilledCircle(
			this->position->x,
			this->position->y,
			this->radius,
			360
		);
	}

	void update() {
		if (
			this->moveUp &&
			this->position->y + this->radius + this->speed->y < this->moveAreaLimits->north
			) this->position->y += this->speed->y;
		if (
			this->moveRight &&
			this->position->x + this->radius + this->speed->x < this->moveAreaLimits->east
			) this->position->x += this->speed->x;
		if (
			this->moveDown &&
			this->position->y - this->radius - this->speed->y > this->moveAreaLimits->south
			) this->position->y -= this->speed->y;
		if (
			this->moveLeft &&
			this->position->x - this->radius - this->speed->x > this->moveAreaLimits->west
			) this->position->x -= this->speed->x;
	}
};
