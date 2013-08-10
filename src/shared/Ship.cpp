/*
 * Ship.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "Ship.hpp"

Ship::Ship() : Entity(0,0,0,0) {

	setType(SHIP);

	setRotation(0);
}

Ship::Ship(float x, float y, float velX, float velY, float rotation) : Entity(x,y,velX,velY) {

	setRotation(rotation);
}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}

float Ship::getRotation() const {
	return rotation;
}

void Ship::update() {

}

void Ship::setRotation(float rotation) {
	this->rotation = rotation;
}
