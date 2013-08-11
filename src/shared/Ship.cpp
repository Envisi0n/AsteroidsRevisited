/*
 * Ship.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "Ship.hpp"
#include <sstream>

Ship::Ship() : Entity(0,0,0,0) {


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

void Ship::setRotation(float rotation) {
	this->rotation = rotation;
}
