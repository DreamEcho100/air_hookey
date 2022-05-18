#include <windows.h>
#include <gl/gl.h>
#include<math.h>

extern float M_PI = 3.14159265358979323846;

// https://stackoverflow.com/a/25423759/13961420
void drawUnfilledCircle(float xi, float yj, float r1, int num1)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num1; i++)
	{
		float theta = 2.0f * M_PI * float(i) / float(num1);
		float x1 = r1 * cosf(theta);
		float y1 = r1 * sinf(theta);
		glVertex2f(xi + x1, yj + y1);
	}
	glEnd();
}
void drawFilledCircle(float xi, float yj, float r1, int num1)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xi, yj);
	for (int i = 0; i <= num1; i++)
	{
		float theta = 2.0f * M_PI * float(i) / float(num1);
		float x1 = r1 * cosf(theta);
		float y1 = r1 * sinf(theta);
		glVertex2f(xi + x1, yj + y1);
	}
	glEnd();
}
