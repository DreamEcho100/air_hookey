#pragma once

#include <windows.h>
#include <gl/gl.h>

//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glut32.lib")

class GlColor4fRGB
{
public:
	float r;
	float g;
	float b;
	float a;

public:
	GlColor4fRGB() = default;
	GlColor4fRGB(
		float r,
		float g,
		float b,
		float a
	) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void applyGLColor() {
		glColor4f(r, g, b, a);
	}
};
