// Striker
#pragma once

#include <windows.h>
#include <gl/gl.h>
#include<math.h>
#include <iostream>

#include "Vector.h"
#include "GlColor4fRGB.h"
#include "CustomOpenGLUtils.h"
#include "CustomOpenGLRect.h"
#include "StrikerMoveAreaLimits.h"

#include "Ball2d.cpp"

using namespace std;

#define M_PI 3.1479265358979323846

class Striker : public Ball2d
{
public:
	Vector *position;
	float radius;
	Vector *velocity;
	Vector *acc;
	GlColor4fRGB *glColor3fRGB;
	StrikerMoveAreaLimits *moveAreaLimits;
	//
	CustomOpenGLRect *goal;
	//
	boolean moveRight = false;
	boolean moveLeft = false;
	boolean moveUp = false;
	boolean moveDown = false;
	//
	bool isIncreasingVelocityXPositive = false;
	bool isIncreasingVelocityYPositive= false;

public:
	Striker() = default;
	Striker(
		Vector* position,
		float radius,
		Vector* velocity,
		Vector* acc,
		GlColor4fRGB* glColor3fRGB,
		StrikerMoveAreaLimits* moveAreaLimits,
		//
		CustomOpenGLRect *goal
	): Ball2d(
		position,
		radius,
		velocity,
		acc,
		glColor3fRGB,
		moveAreaLimits
	) {
		this->position = position;
		this->radius = radius;
		this->velocity = velocity;
		this->acc = acc;
		this->glColor3fRGB = glColor3fRGB;
		this->moveAreaLimits = moveAreaLimits;
		//
		this->goal = goal;
	}

	void increaseVelocityX() {
		if (this->isIncreasingVelocityXPositive) {
			if (this->velocity->x < 7) this->velocity->x += 0.1;
		} else if (this->velocity->x > -7) this->velocity->x -= 0.1;
	}
	void decreaseVelocityX() {
				//// if (this->velocity->x > 0) this->velocity->x -= 0.1;
				//if (this->isIncreasingVelocityXPositive && this->velocity->x < 0) this->velocity->x -= 0.1;
				//else if (!this->isIncreasingVelocityXPositive && this->velocity->x > 0) this->velocity->x += 0.1;
		if (this->isIncreasingVelocityXPositive) {
			if (this->velocity->x > 0) this->velocity->x -= 0.1;
		}
		else if (this->velocity->x < 0) this->velocity->x += 0.1;
	}

	//void increaseVelocityY() {
	//			if (this->isIncreasingVelocityYPositive && this->velocity->y < 7) this->velocity->y += 0.1;
	//			else if (!this->isIncreasingVelocityYPositive && this->velocity->y > -7) this->velocity->y -= 0.1;
	//}
	//void decreaseVelocityY() {
	//			// if (this->velocity->y > 0) this->velocity->y -= 0.1;
	//			if (this->isIncreasingVelocityYPositive && this->velocity->y < 0) this->velocity->y -= 0.1;
	//			else if (!this->isIncreasingVelocityYPositive && this->velocity->y > 0) this->velocity->y += 0.1;
	//}
	void increaseVelocityY() {
		if (this->isIncreasingVelocityYPositive) {
			if (this->velocity->y < 7) this->velocity->y += 0.1;
		}
		else if (this->velocity->y > -7) this->velocity->y -= 0.1;
	}
	void decreaseVelocityY() {
		if (this->isIncreasingVelocityYPositive) {
			if (this->velocity->y > 0) this->velocity->y -= 0.1;
		}
		else if (this->velocity->y < 0) this->velocity->y += 0.1;
	}

	void update() {
		bool isIncreasingVelocityX = false;
		bool isIncreasingVelocityY= false;
		if (
			this->moveUp &&
			this->position->y + this->radius + this->velocity->y < this->moveAreaLimits->north
			) {
				this->position->y += this->velocity->y;
				isIncreasingVelocityY = true;
				// this->isIncreasingVelocityYPositive = true;
				if(
					this->velocity->y != 0 && !this->isIncreasingVelocityYPositive
				) {
					this->velocity->y = 0;
					this->isIncreasingVelocityYPositive = true;
				}
			}
		if (
			this->moveRight &&
			this->position->x + this->radius + this->velocity->x < this->moveAreaLimits->east
			) {
				this->position->x += this->velocity->x;
				isIncreasingVelocityX = true;
				if(
					this->velocity->x != 0 && !this->isIncreasingVelocityXPositive
				) {
					this->velocity->x = 0;
					this->isIncreasingVelocityXPositive = true;
				}
			}
		if (
			this->moveDown &&
			this->position->y - this->radius - this->velocity->y > this->moveAreaLimits->south
			) {
				this->position->y += this->velocity->y;
				isIncreasingVelocityY = true;
				// this->isIncreasingVelocityYPositive = false;
				if(
					this->velocity->y != 0 && this->isIncreasingVelocityYPositive
				) {
					this->velocity->y = 0;
					this->isIncreasingVelocityYPositive = false;
				}
			}
		if (
			this->moveLeft &&
			this->position->x - this->radius - this->velocity->x > this->moveAreaLimits->west
			) {
				this->position->x += this->velocity->x;
				isIncreasingVelocityX = true;
				if(
					this->velocity->x != 0 && this->isIncreasingVelocityXPositive
				) {
					this->velocity->x = 0;
					this->isIncreasingVelocityXPositive = false;
				}
			}

			if (isIncreasingVelocityY)
				this->increaseVelocityY();
				else this->decreaseVelocityY();
			if (isIncreasingVelocityX)
				this->increaseVelocityX();
				else this->decreaseVelocityX();
	}
};
