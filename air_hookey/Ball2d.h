#include "Vector.h"
#include "GlColor4fRGB.h"
#include "StrikerMoveAreaLimits.h"
#include "CustomOpenGLUtils.h"

#pragma once

class Ball2d
{
public:
	Vector* position;
	float radius;
	Vector* velocity;
	Vector* acc;
	float acceleration = 1;
	GlColor4fRGB* glColor3fRGB;
	StrikerMoveAreaLimits* moveAreaLimits;
	float friction = 0.0;

public:
	//Ball2d() = default;
	Ball2d(
		Vector* position,
		float radius,
		Vector* velocity,
		Vector * acc,
		GlColor4fRGB * glColor3fRGB,
		StrikerMoveAreaLimits * moveAreaLimits
	) {
		this->position = position;
		this->radius = radius;
		this->velocity = new Vector(0, 0);
		this->acc = new Vector(0, 0);
		this->glColor3fRGB = glColor3fRGB;
		this->moveAreaLimits = moveAreaLimits;
	}

	void draw() {
		this->glColor3fRGB->applyGLColor();
		drawFilledCircle(
			this->position->x,
			this->position->y,
			this->radius,
			360
		);
	}
};

