/*
 * Entity.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "Entity.hpp"
#include "GameGlobals.hpp"
#include <iostream>
#include <sstream>

unsigned int Entity::nextID = 0;

Entity::Entity() {

	id = nextID++;

	setX(0);
	setY(0);
	setVelX(1);
	setVelY(1);

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

Entity::Entity(float x, float y, float velX, float velY) {
	setX(x);
	setY(y);
	setVelX(velX);
	setVelY(velY);
}

void Entity::setY(float y) {
	this->y = y;
}

void Entity::update() {

	if (getX() + getVelX() > WORLD_WIDTH || getX() + getVelX() < 0)
		setVelX(-getVelX());
	if (getY() + getVelY() > WORLD_HEIGHT || getY() + getVelY() < 0)
		setVelY(-getVelY());

	setX(getX() + getVelX());
	setY(getY() + getVelY());

}

float Entity::getVelX() const {
	return velX;
}

void Entity::setVelX(float velX) {
	this->velX = velX;
}

float Entity::getVelY() const {
	return velY;
}

std::string Entity::toString() {

	std::stringstream tmp;

	tmp << "[" << getId() << "] x=" << getX() << " y=" << getY() << " vX="
			<< getVelX() << " vY=" << getVelY();

	return tmp.str();

}

void Entity::setVelY(float velY) {
	this->velY = velY;
}

void Entity::toPacket(sf::Packet* packet) {

	*packet << getX();
	*packet << getY();

}

unsigned int Entity::getId() const {
	return id;
}
