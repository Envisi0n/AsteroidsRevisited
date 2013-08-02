/*
 * World.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "World.hpp"
#include "Net_shared.hpp"
#include <iostream>
World::World() {
	// TODO Auto-generated constructor stub

	entities.push_back(new Entity());
}

void World::update() {

	for (std::vector<Entity*>::iterator it = entities.begin();
			it != entities.end(); ++it) {

		(*it)->update();
	}

}

World::~World() {
	// TODO Auto-generated destructor stub
}

sf::Packet World::toPacket() {

	short packetType;
	sf::Packet gamePacket;

	packetType = SERVER_UPDATE;
	gamePacket << packetType;

	for (std::vector<Entity*>::iterator it = entities.begin();
			it != entities.end(); ++it) {
		gamePacket << (*it)->getX();
		gamePacket << (*it)->getY();

	}

	return gamePacket;

}
