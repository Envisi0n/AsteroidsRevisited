/*
 * Entity.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "Entity.hpp"
#include "GameGlobals.hpp"

Entity::Entity() {
	setX(0);
	setY(0);
	velX = 1;
	velY = 1;

}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

float Entity::getX() const {
	return x;
}

void Entity::setX(float x) {
	this->x = x;
}

float Entity::getY() const {
	return y;
}

Entity::Entity(float x, float y) {
	setX(x);
	setY(y);
}

void Entity::setY(float y) {
	this->y = y;
}

void Entity::update() {

	if( getX()+velX > WORLD_WIDTH || getX()+velX < 0 )
		velX = -velX;
	if( getY()+velY > WORLD_HEIGHT || getY()+velY < 0 )
		velY = -velY;


	setX(getX()+velX);
	setY(getY()+velY);
}
