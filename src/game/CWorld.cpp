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

	float tmpX;
	float tmpY;

	// Nothing in here yet
	if (centities.empty()) {
		while (!packet.endOfPacket()) {

			packet >> tmpX;
			packet >> tmpY;

			centities.push_back(new CEntity(tmpX, tmpY,0,0));
		}

		return;
	}
	// We already have things
	else {

		for (std::vector<CEntity*>::iterator it = centities.begin();
				it != centities.end(); ++it) {

			packet >> tmpX;
			packet >> tmpY;

			(*it)->setPosition(tmpX, tmpY);

		}
		// Add anything not updated
		while (!packet.endOfPacket()) {

			packet >> tmpX;
			packet >> tmpY;

			centities.push_back(new CEntity(tmpX, tmpY,0,0));
		}
	}

}
