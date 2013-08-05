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
	entities.push_back(new Entity(100, 100));
	entities.push_back(new Entity(200, 200));
	entities.push_back(new Entity(300, 300));
	entities.push_back(new Entity(400, 400));
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

void World::createPlayer(int client, std::string userName) {
	players.push_back(new Player(client, userName));
}

void World::removePlayer(int client) {

	for (std::vector<Player*>::iterator it = players.begin();
			it != players.end(); ++it) {
		if ((*it)->getClientId() == client) {
			delete (*it);
			players.erase(it);
			return;
		}
	}
}

void World::removePlayer(std::string userName) {

	for (std::vector<Player*>::iterator it = players.begin();
			it != players.end(); ++it) {
		if ((*it)->getUserName() == userName) {
			delete (*it);
			players.erase(it);
			return;
		}
	}
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
