#include <windows.h>
#include <gl/gl.h>
#include <iostream>

#include "GlColor4fRGB.h"

#pragma once
class CustomOpenGLRect
{
public:
	float positionX;
	float positionY;
	float width;
	float height;
	GlColor4fRGB glColor3fRGB;

public:
	CustomOpenGLRect() = default;
	CustomOpenGLRect(
		float positionX,
		float positionY,
		float width,
		float height,
		GlColor4fRGB& glColor3fRGB
	) {
		this->positionX = positionX;
		this->positionY = positionY;
		this->width = width;
		this->height = height;
		this->glColor3fRGB = glColor3fRGB;
	}

	void draw() {
		//
		glBegin(GL_QUADS);
		this->glColor3fRGB.applyGLColor();
		glVertex2f(this->positionX, this->positionY);
		glVertex2f(this->positionX + this->width, this->positionY);
		glVertex2f(this->positionX + this->width, this->positionY - this->height);
		glVertex2f(this->positionX, this->positionY - this->height);

		glEnd();
	}

};

