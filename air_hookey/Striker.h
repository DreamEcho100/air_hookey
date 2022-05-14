#pragma once

#include "GlColor4fRGB.h"

using namespace std;

class Striker
{
public:
	float positionX;
	float positionY;
	float velocityX;
	float velocityY;
	float radius;
	GlColor4fRGB glColor3fRGB;
	float speed;

public:
	Striker() = default;
	Striker(
		float positionX,
		float positionY,
		float velocityX,
		float velocityY,
		float radius,
		GlColor4fRGB &glColor3fRGB,
		float speed
	) {
		this -> positionX = positionX;
		this -> positionY = positionY;
		this -> velocityX = velocityX;
		this -> velocityY = velocityY;
		this -> radius = radius;
		this-> glColor3fRGB = glColor3fRGB;
		this -> speed = speed;
	}

	void draw() {}

	void update() {}
};

