#include <list>
//#include <iostrem>

#include "Vector.h"
#include "GlColor4fRGB.h"
#include "StrikerMoveAreaLimits.h"
#include "Striker.h"
#include "collisionUtils.h"
//
#include "Ball2d.cpp"

#pragma once

//extern float M_PI = 3.14159265358979323846;
class Puck: public Ball2d
{
public:
	Vector *position;
	float radius;
	Vector *velocity;
	Vector *acc;
	float acceleration = 1;
	GlColor4fRGB *glColor3fRGB;
	StrikerMoveAreaLimits *moveAreaLimits;
	Striker* player1;
	Striker* player2;
	//Striker *players[];
	float moveCounter = 0;

public:
	Puck() = default;
	Puck(
		Vector *position,
		float radius,
		Vector *velocity,
		Vector *acc,
		GlColor4fRGB *glColor3fRGB,
		StrikerMoveAreaLimits *moveAreaLimits,
		Striker* player1,
		Striker* player2
		//Striker *players[]
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
		this->player1 = player1;
		this->player2 = player2;
		//this->players = players;
	}

	void update() {
		if (this->moveCounter > 0) {
			//double x = moveCounter * 0.01;
			if (
				this->position->x + this->velocity->x + (this->velocity->x / this->velocity->x) * 2> moveAreaLimits->east ||
				this->position->x + this->velocity->x + (this->velocity->x / this->velocity->x) * 2< moveAreaLimits->west
				) {
					this->position->add(new Vector(this->velocity->x * -1, 0));
					this->velocity->x *= -1;
					}
			if (
				this->position->y + this->velocity->y + (this->velocity->y / this->velocity->y) * 2> moveAreaLimits->north
				||
				this->position->y + this->velocity->y + (this->velocity->y / this->velocity->y) * 2< moveAreaLimits->south
				) {
					this->position->add(new Vector(0, this->velocity->y * -1));
					this->velocity->y *= -1;
					}

			this->position->add(this->velocity);
			this->moveCounter -= 15;
		}

		float dx = this->position->x - this->player1->position->x;
		float dy = this->position->y - this->player1->position->y;

		float distance = sqrt((dx * dx) + (dy * dy));

		if (distance < (this->radius + this->player1->radius)) {
			this->resolveCollision(player1);
			player1->position->add(new Vector(player1->velocity->x * -1, player1->velocity->y * -1));
			this->moveCounter = 2500;

		}

		dx = this->position->x - this->player2->position->x;
		dy = this->position->y - this->player2->position->y;

		distance = sqrt((dx * dx) + (dy * dy));

		if (distance < (this->radius + this->player2->radius)) {
			this->resolveCollision(player2);
			player2->position->add(new Vector(player2->velocity->x * -1, player2->velocity->y * -1));
			this->moveCounter = 2500;
		}
	}

	// isCollide(aReact, bRect) {
	// 	return !(
	// 		(aReact.bottom < bRect.top) || (aReact.top > bRect.bottom) || (aReact.right < bRect.left) || (aReact.left > bRect.right)
	// 		)
	// }

	/**
	 * Rotates coordinate system for velocities
	 *
	 * Takes velocities and alters them as if the coordinate system they're on was rotated
	 *
	 * @param  Object | velocity | The velocity of an individual particle
	 * @param  Float  | angle    | The angle of collision between two objects in radians
	 * @return Object | The altered x and y velocities after the coordinate system has been rotated
	 */
	Vector* rotate(Vector* velocity, float angle) {
		return new Vector(
			velocity->x * cos(angle) - velocity->y * sin(angle),
			velocity->x * sin(angle) + velocity->y * cos(angle)
		);
	}

	/**
	 * Swaps out two colliding particles' x and y velocities after running through
	 * an elastic collision reaction equation
	 *
	 * @param  Object | player      | A player object with x and y coordinates, plus velocity
	 * @return Null | Does not return a value
	 */
	void resolveCollision(Striker*player) {
		float xVelocityDiff = player->velocity->x - this->velocity->x;
		float yVelocityDiff = player->velocity->y - this->velocity->y;

		float xDist = this->position->x - player->position->x;
		float yDist = this->position->y - player->position->y;

		// Prevent accidental overlap of players
		if (xVelocityDiff * xDist + yVelocityDiff * yDist >= 0) {

			// Grab angle between the two colliding players
			float angle = -atan2(this->position->y - player->position->y, this->position->x - player->position->x);

			// Store mass in var for better readability in collision equation
			float m1 = player->radius;
			float m2 = this->radius;

			// Velocity before equation
			Vector* u1 = rotate(player->velocity, angle);
			Vector* u2 = rotate(this->velocity, angle);
			
			// Velocity after 1d collision equation
			Vector* v1 = new Vector(u1->x * (m1 - m2) / (m1 + m2) + u2->x * 2 * m2 / (m1 + m2), u1->y );
			Vector* v2 = new Vector(u2->x * (m1 - m2) / (m1 + m2) + u1->x * 2 * m2 / (m1 + m2), u2->y );

			// Final velocity after rotating axis back to original location
			Vector* vFinal1 = rotate(v1, -angle);
			Vector* vFinal2 = rotate(v2, -angle);
			
			// Swap player velocities for realistic bounce effect
			//player->velocity->x = vFinal1->x;
			//player->velocity->y = vFinal1->y;

			this->velocity->x = vFinal2->x;
			this->velocity->y = vFinal2->y;
		}
	}
};
