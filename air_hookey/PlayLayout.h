#pragma once

#include <windows.h>
#include <gl/gl.h>

#include "GlColor4fRGB.h"

class PlayLayout
{

public:

	float canvasXAxis;
	float canvasYAxis;
	GlColor4fRGB canvasGlColor3fRGB;
	float borderY;
	float borderX;
	GlColor4fRGB borderGlColor3fRGB;
	float fieldY;
	float fieldX;
	GlColor4fRGB fieldGlColor3fRGB;

public:
	PlayLayout() = default;
	PlayLayout(
		float canvasXAxis,
		float canvasYAxis,
		GlColor4fRGB& canvasGlColor3fRGB,
		float borderY,
		float borderX,
		GlColor4fRGB& borderGlColor3fRGB,
		float fieldY,
		float fieldX,
		GlColor4fRGB& fieldGlColor3fRGB
	)
	{
		this->canvasXAxis = canvasXAxis;
		this->canvasYAxis = canvasYAxis;
		this->canvasGlColor3fRGB = canvasGlColor3fRGB,
		this->borderY = borderY;
		this->borderX = borderX;
		this->borderGlColor3fRGB = borderGlColor3fRGB;
		this->fieldY = fieldY;
		this->fieldX = fieldX;
		this->fieldGlColor3fRGB = fieldGlColor3fRGB;
	}


	void draw() {
		//
		glBegin(GL_QUADS);

		this->canvasGlColor3fRGB.applyGLColor();
		glVertex2f(this->canvasYAxis, -this->canvasXAxis);
		glVertex2f(this->canvasYAxis, this->canvasXAxis);
		glVertex2f(-this->canvasYAxis, this->canvasXAxis);
		glVertex2f(-this->canvasYAxis, -this->canvasXAxis);

		glEnd();

		//
		glBegin(GL_QUADS);
		this->borderGlColor3fRGB.applyGLColor();

		glVertex2f(this->borderY, -this->borderX);
		glVertex2f(this->borderY, this->borderX);
		glVertex2f(-this->borderY, this->borderX);
		glVertex2f(-this->borderY, -this->borderX);

		glEnd();

		//
		glBegin(GL_QUADS);
		this->fieldGlColor3fRGB.applyGLColor();

		glVertex2f(this->fieldY, -this->fieldX);
		glVertex2f(this->fieldY, this->fieldX);
		glVertex2f(-this->fieldY, this->fieldX);
		glVertex2f(-this->fieldY, -this->fieldX);

		glEnd();
	}

};

