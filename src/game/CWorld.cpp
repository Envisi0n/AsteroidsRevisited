/*
 * CWorld.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "CWorld.hpp"
#include "../shared/Net_shared.hpp"
#include <iostream>
#include "ResourceManager.hpp"

CWorld::CWorld() {
	// TODO Auto-generated constructor stub

}

CWorld::~CWorld() {
	// TODO Auto-generated destructor stub
}

void CWorld::draw(sf::RenderWindow* window) {

	for (std::vector<CEntity*>::iterator it = centities.begin();
			it != centities.end(); ++it) {
		(*it)->draw(window);
	}

	for (std::vector<CPlayer*>::iterator it = cplayers.begin();
			it != cplayers.end(); ++it) {
		(*it)->draw(window);
	}

}

void CWorld::update(sf::Event event) {
	for (std::vector<CEntity*>::iterator it = centities.begin();
			it != centities.end(); ++it) {
		(*it)->update(event);
	}

}

void CWorld::packetToWorld(sf::Packet packet) {

	unsigned int type;

	while (!packet.endOfPacket()) {

		// Determine type of object
		packet >> type;

		switch (type) {

		case ENTITY:
			handleEntityPacket(&packet);
			break;
		case PLAYER:
			handlePlayerPacket(&packet);
			break;
		case ASTEROID:
			//	handleAsteroidPacket(&packet);
			break;

		}

	}

}

void CWorld::handleEntityPacket(sf::Packet* packet) {

	CEntity *tmp = new CEntity();

	tmp->fromPacket(packet);
	// Nothing currently in entities
	if (centities.empty()) {
		centities.push_back(tmp);
		return;
	}

	// Need update entity
	for (std::vector<CEntity*>::iterator it = centities.begin();
			it != centities.end(); ++it) {
		if ((*it)->getId() == tmp->getId()) {
			(*it)->setPosition(tmp->getX(), tmp->getY());
			delete tmp;
			return;
		}

	}

	// This entity is new

	centities.push_back(tmp);

}

void CWorld::handlePlayerPacket(sf::Packet* packet) {

	CPlayer *tmp = new CPlayer();

	tmp->fromPacket(packet);

	// Nothing currently in players
	if (cplayers.empty()) {

		// Prepare ship
		tmp->setShipTexture(ResourceManager::loadTexture("images/ship.png"));

		std::cout << "Created player" << std::endl;
		std::cout << tmp->toString() << std::endl;
		cplayers.push_back(tmp);
		return;
	}

}
