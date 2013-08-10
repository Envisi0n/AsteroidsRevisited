/*
 * CWorld.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "CWorld.hpp"
#include "../shared/Net_shared.hpp"
#include <iostream>

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

}

void CWorld::update(sf::Event event) {
	for (std::vector<CEntity*>::iterator it = centities.begin();
			it != centities.end(); ++it) {
		(*it)->update(event);
	}

}

void CWorld::packetToWorld(sf::Packet packet) {

	unsigned int type;

	while( !packet.endOfPacket() ) {

		// Determine type of object
		packet >> type;

		switch(type) {

		case ENTITY:
			handleEntityPacket(&packet);
			break;
		case SHIP:
		//	handleShipPacket(&packet);
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

	centities.push_back(tmp);

}
