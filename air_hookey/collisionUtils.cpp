#include <math.h>
#include <iostream>

bool collisionBetweenTwoCircles(
	float x1, float y1, float r1,
	float x2, float y2, float r2
) {

	//return (x2 - x1) * 2 + (y2 - y1) * 2 <= (r1 + r2) * 2;

	float x = x1 - x2;
	float y = y1 - y2;

	float distance = sqrt((x * x) + (y * y));

	return distance < (r1 + r2);
}