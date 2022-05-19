#include <list>
//#include <iostrem>

#include "Vector.h"
#include "GlColor4fRGB.h"
#include "StrikerMoveAreaLimits.h"
#include "Striker.h"
#include "collisionUtils.h"

#pragma once

//extern float M_PI = 3.14159265358979323846;
class Puck
{
public:
	Vector *position;
	float radius;
	Vector *speed;
	Vector *velocity;
	Vector *acc;
	float acceleration = 1;
	GlColor4fRGB *glColor3fRGB;
	StrikerMoveAreaLimits *moveAreaLimits;
	Striker* player1;
	Striker* player2;
	//Striker *players[];
	float endX = 0;
	float endY = 0;

public:
	Puck() = default;
	Puck(
		Vector *position,
		float radius,
		Vector *speed,
		Vector *velocity,
		Vector *acc,
		GlColor4fRGB *glColor3fRGB,
		StrikerMoveAreaLimits *moveAreaLimits,
		Striker* player1,
		Striker* player2
		//Striker *players[]
	) {
		this->position=position;
		this->radius=radius;
		this->speed=speed;
		this->velocity=velocity;
		this->acc=acc;
		this->glColor3fRGB = glColor3fRGB;
		this->moveAreaLimits = moveAreaLimits;
		this->player1 = player1;
		this->player2 = player2;
		//this->players = players;
	}

	void draw() {
		this->glColor3fRGB->applyGLColor();
		drawFilledCircle(
			this->position->x,
			this->position->y,
			this->radius,
			360
		);
	}

	void update() {
		if (this->endX != 0) {
			double x = endX * 0.01;
			this->position->x += x;
			this->endX -= x;
		}
		if (this->endY != 0) {
			double y = endY * 0.01;
			this->position->y -= y;
			this->endY -= y;
		}
		float dx = this->position->x - this->player1->position->x;
		float dy = this->position->y - this->player1->position->y;

		float distance = sqrt((dx * dx) + (dy * dy));

		//float forceDirectionX = dx / distance;
		//float forceDirectionY = dy / distance;
		//// Max distance, past that the force will be 0
		//int maxDistance = 100;
		//float force = (maxDistance - distance) / maxDistance;
		//if (force < 0) force = 0;
		//float directionX = forceDirectionX * force * this->speed->x * 0.6;
		//float directionY = forceDirectionY * force * this->speed->y * 0.6;

		if (distance < (this->radius + this->player1->radius)) {
			//this->position->x -= directionX * 1.5;
			//this->position->y -= directionY * 1.5;
			std::cout << "1" << std::endl;
			// calculateNewVelocities(player1);

		}

		dx = this->position->x - this->player2->position->x;
		dy = this->position->y - this->player2->position->y;

		distance = sqrt((dx * dx) + (dy * dy));

		if (distance < (this->radius + this->player2->radius)) {
			std::cout << "2" << std::endl;
		}
	}

	void calculateNewVelocities(Striker *player) {
			    double mass1 = player->radius;
                double mass2 = this->radius;
                double velX1 = player->velocity->x;
                double velX2 = this->velocity->x;
                double velY1 = player->velocity->y;
                double velY2 = this->velocity->y;
                
                double newVelX1 = (velX1 * (mass1 - mass2) + (2 * mass2 * velX2)) / (mass1 + mass2);
                double newVelX2 = (velX2 * (mass2 - mass1) + (2 * mass1 * velX1)) / (mass1 + mass2);
                double newVelY1 = (velY1 * (mass1 - mass2) + (2 * mass2 * velY2)) / (mass1 + mass2);
                double newVelY2 = (velY2 * (mass2 - mass1) + (2 * mass1 * velY1)) / (mass1 + mass2);
                // trace (velX1 * (mass1 - mass2) );
								// trace (2 * mass2 * velX2);
								// trace(newVelX1);
								// double s = 0 / 20;
								// trace(s);
				
				
                //player->velocity->x = newVelX1;
                this->velocity->x = newVelX2;
                //player->velocity->y = newVelY1;
                this->velocity->y = newVelY2;
                
                //player->position->x = player->position->x + newVelX1;
                //player->position->y = player->position->y + newVelY1;
                this->endX = this->position->x + newVelX2;
                this->endY = this->position->y + newVelY2;
		}

	// isCollide(aReact, bRect) {
	// 	return !(
	// 		(aReact.bottom < bRect.top) || (aReact.top > bRect.bottom) || (aReact.right < bRect.left) || (aReact.left > bRect.right)
	// 		)
	// }

/*
//collision resolution
//calculates the balls new velocity vectors after the collision
	void coll_res_bb(b1, b2){
		//collision normal vector
		let normal = b1.pos.subtr(b2.pos).unit();
		//relative velocity vector
		let relVel = b1.vel.subtr(b2.vel);
		//separating velocity - relVel projected onto the collision normal vector
		let sepVel = Vector.dot(relVel, normal);
		//the projection value after the collision (multiplied by -1)
		let new_sepVel = -sepVel;
		//collision normal vector with the magnitude of the new_sepVel
		let sepVelVec = normal.mult(new_sepVel);

		//adding the separating velocity vector to the original vel. vector
		b1.vel = b1.vel.add(sepVelVec);
		//adding its opposite to the other balls original vel. vector
		b2.vel = b2.vel.add(sepVelVec.mult(-1));
	}
	*/
};
/*
update() {
	context.fillStyle = this.color;
	// Collision detection
	const dx = mouse.x - this.x;
	const dy = mouse.y - this.y;
	const distance = Math.sqrt(dx ** 2 + dy ** 2);
	const forceDirectionX = dx / distance;
	const forceDirectionY = dy / distance;

	// Max distance, past that the force will be 0
	const maxDistance = 100;
	let force = (maxDistance - distance) / maxDistance;
	//if (force < 0) force = 0;

	const directionX = forceDirectionX * force * this.density * 0.6;
	const directionY = forceDirectionY * force * this.density * 0.6;

	if (distance < mouse.radius + this.size) {
		this.x -= directionX * 1.5;
		this.y -= directionY * 1.5;
	} else {
		if (this.x !== this.baseX) {
			this.x -= (this.x - this.baseX) / 20;
		}
		if (this.y !== this.baseY) {
			this.y -= (this.y - this.baseY) / 20;
		}
	}

	this.draw();
}
*/
