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

	// Slow down
	setVelX(getVelX()*SLOWDOWN);
	setVelY(getVelY()*SLOWDOWN);

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

	if (direction == REVERSE) {

		setVelX(getVelX() + ACCELERATION * std::cos(getRotation()/3.14*180.0));
		setVelY(getVelY() + ACCELERATION * std::sin(getRotation()/3.14*180.0));

		if (getVelX() > MAXSPEED)
			setVelX(MAXSPEED);
		if (getVelY() > MAXSPEED)
			setVelY(MAXSPEED);
		return;

	} else {

		setVelX(getVelX() - ACCELERATION * std::cos(getRotation()/3.14*180.0));
		setVelY(getVelY() - ACCELERATION * std::sin(getRotation()/3.14*180.0));

		if (getVelX() < -MAXSPEED)
			setVelX(-MAXSPEED);
		if (getVelY() < -MAXSPEED)
			setVelY(-MAXSPEED);

		return;

	}

}

void Ship::clientUpdate(int clientAction) {

	switch (clientAction) {
	case THRUSTUP:
		thrust(FORWARD);
		break;
	case THRUSTDOWN:
		thrust(REVERSE);
		break;
	case TURNLEFT:
		turn(LEFT);
		break;
	case TURNRIGHT:
		turn(RIGHT);
		break;
	}
}

void Ship::turn(int direction) {

	if (direction == LEFT) {

		if (getRotation() - TURNSPEED < 0) {
			setRotation(360-TURNSPEED);
		} else {

			setRotation(getRotation() - TURNSPEED);
		}
	} else {

		if (getRotation() + TURNSPEED > 360) {
			setRotation(0);
		} else {

			setRotation(getRotation() + TURNSPEED);
		}
	}
}

void Ship::setRotation(float rotation) {
	this->rotation = rotation;
}
