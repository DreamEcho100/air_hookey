#include <windows.h>
#include <gl/gl.h>

#include "GlColor4fRGB.h"
#include "Vector.h"

#pragma once
class CustomOpenGLRect
{
public:
	Vector *position;
	float width;
	float height;
	GlColor4fRGB glColor3fRGB;

public:
	CustomOpenGLRect() = default;
	CustomOpenGLRect(
		Vector *position,
		float width,
		float height,
		GlColor4fRGB& glColor3fRGB
	) {
		this->position = position;
		this->width = width;
		this->height = height;
		this->glColor3fRGB = glColor3fRGB;
	}

	void draw() {
		//
		glBegin(GL_QUADS);
		this->glColor3fRGB.applyGLColor();
		glVertex2f(this->position->x, this->position->y);
		glVertex2f(this->position->x + this->width, this->position->y);
		glVertex2f(this->position->x + this->width, this->position->y - this->height);
		glVertex2f(this->position->x, this->position->y - this->height);

		glEnd();
	}

};

