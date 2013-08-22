/*
 * Ship.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "Ship.hpp"
#include <sstream>
#include <cmath>
#include <iostream>
#include "GameGlobals.hpp"

Ship::Ship() :
		Entity(0, 0, 0, 0) {

	setRotation(0);
}

Ship::Ship(float x, float y, float velX, float velY, float rotation) :
		Entity(x, y, velX, velY) {

	setRotation(rotation);
}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}

float Ship::getRotation() const {
	return rotation;
}

void Ship::update() {
	Entity::update();

}

void Ship::toPacket(sf::Packet* packet) {

	Entity::toPacket(packet);
	*packet << getRotation();
}

void Ship::fromPacket(sf::Packet* packet) {

	float rotation;

	Entity::fromPacket(packet);
	*packet >> rotation;

	setRotation(rotation);
}

std::string Ship::toString() {

	std::stringstream tmp;

	tmp << Entity::toString();

	tmp << " rotation=" << getRotation();

	return tmp.str();

}

void Ship::thrust(int direction) {

	if (direction == FORWARD) {

		setVelX(getVelX() + ACCELERATION * std::cos(getRotation()));
		setVelY(getVelY() + ACCELERATION * std::sin(getRotation()));

		if (getVelX() > MAXSPEED)
			setVelX(MAXSPEED);
		if (getVelY() > MAXSPEED)
			setVelY(MAXSPEED);
		return;

	} else {

		setVelX(getVelX() - ACCELERATION * std::cos(getRotation()));
		setVelY(getVelY() - ACCELERATION * std::sin(getRotation()));

		if (getVelX() < -MAXSPEED)
			setVelX(-MAXSPEED);
		if (getVelY() < -MAXSPEED)
			setVelY(-MAXSPEED);

		return;

	}

}

void Ship::clientUpdate(int clientAction) {

	switch( clientAction ) {
	case THRUSTUP:
		thrust(FORWARD);
		break;
	case THRUSTDOWN:
		thrust(REVERSE);
		break;
	}

}

void Ship::turn(int direction) {

	if (direction == LEFT) {

	} else {

	}

}

void Ship::setRotation(float rotation) {
	this->rotation = rotation;
}
