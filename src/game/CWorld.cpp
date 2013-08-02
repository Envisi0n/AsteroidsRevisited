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

	short packetType;
	float tmpX;
	float tmpY;

	packet >> packetType;

	if (packetType != SERVER_UPDATE) {
		std::cout << "NOT A SERVER UPDATE PACKET" << std::endl;
	}

	// Nothing in here yet
	if (centities.empty()) {
		while (!packet.endOfPacket()) {

			packet >> tmpX;
			packet >> tmpY;

			centities.push_back(new CEntity(tmpX, tmpY));
		}

		return;
	}

	for (std::vector<CEntity*>::iterator it = centities.begin();
			it != centities.end(); ++it) {

		packet >> tmpX;
		packet >> tmpY;

		(*it)->setPosition(tmpX,tmpY);

	}

}
