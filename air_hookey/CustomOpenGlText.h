#include <gl/glut.h>
#include <string>

#include "Vector.h"
#include "GlColor4fRGB.h"

#pragma once

class CustomOpenGlText
{
public:
	Vector* position;
	GlColor4fRGB* glColor4fRGB;
	/*
	* GLUT_BITMAP_8_BY_13
	* GLUT_BITMAP_9_BY_15
	* GLUT_BITMAP_TIMES_ROMAN_10
	* GLUT_BITMAP_TIMES_ROMAN_24
	* GLUT_BITMAP_HELVETICA_10
	* GLUT_BITMAP_HELVETICA_12
	* GLUT_BITMAP_HELVETICA_18
	*/
	void* font;
	std::string str;

public:
	CustomOpenGlText() = default;
	CustomOpenGlText(
		Vector* position,
		GlColor4fRGB* glColor4fRGB,
		void* font,
		std::string str
	) {
		this->position = position;
		this->glColor4fRGB = glColor4fRGB;
		this->font = font;
		this->str = str;
	}

	void draw()
	{
		//glColor3f(r, g, b);
		glRasterPos2f(this->position->x, this->position->y);
		int len, i;
		//len = (int)strlen(this->text);
		//for (i = 0; i < len; i++) {
		//	glutBitmapCharacter(this->font, this->text[i]);
		//}
		for (std::string::iterator i = str.begin(); i != str.end(); ++i)
		{
			char c = *i;
			this->glColor4fRGB->applyGLColor();
			glutBitmapCharacter(font, c);
		}
	}
};

