#include <math.h>

#pragma once;

class Vector
{
public:
	float x;
	float y;
public:
	Vector() = default;
	Vector(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vector* add(float x, float y){
		this->x += x;
		this->y += y;
		return this;
	}
	Vector* addRNV(Vector* vector){
		return new Vector(this->x+vector->x, this->y+vector->y);
	}
	
	Vector* subtract(float x, float y){
		this->x -= x;
		this->y -= y;
		return this;
	}
	Vector* subtractRNV(Vector* vector){
		return new Vector(this->x-vector->x, this->y-vector->y);
	}

	double magnitude(){
		return sqrt(pow(this->x, 2) + pow(this->y, 2));
	}

	Vector* multiply(float x, float y){
		this->x *= x;
		this->y *= y;
		return this;
	}
	Vector* multiplyRNV(float num){
		return new Vector(this->x*num, this->y*num);
	}

	Vector*	normal(){
		this->y *= -1;
		return this->unit();
	}
	Vector*	normalRNV(){
		Vector *vector = new Vector(-this->y, this->x);
		return vector->unitRNV();
	}

	Vector*	unit(){
		if(this->magnitude() == 0){
			this->x = 0;
			this->y = 0;
			return this;
		} else {
			this->x = this->x/this->magnitude();
			this->y = this->y/this->magnitude();
			return this;
		}
	}
	Vector*	unitRNV(){
		if(this->magnitude() == 0){
			return new Vector(0,0);
		} else {
			return new Vector(this->x/this->magnitude(), this->y/this->magnitude());
		}
	}
};

