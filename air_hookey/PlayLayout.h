#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <iostream>

#include "GlColor4fRGB.h"
#include "CustomOpenGLRect.h"

class PlayLayout
{

public:

	int windowWidth;
	int windowHeight;
	CustomOpenGLRect background;
	CustomOpenGLRect border;
	CustomOpenGLRect field;

public:
	PlayLayout() = default;
	PlayLayout(
		int windowWidth,
		int windowHeight,
		CustomOpenGLRect& background,
		CustomOpenGLRect& border,
		CustomOpenGLRect& field
	)
	{

		this->windowWidth = windowWidth;
		this->windowHeight = windowHeight;

		this->background = background;
		this->border = border;
		this->field = field;
	}

	void draw() {
		this->background.draw();
		this->border.draw();
		this->field.draw();
	}

};

