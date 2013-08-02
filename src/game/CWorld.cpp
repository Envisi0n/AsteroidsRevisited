/*
 * CWorld.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "CWorld.hpp"

CWorld::CWorld() {
	// TODO Auto-generated constructor stub

	entities.push_back(new CEntity());

}

CWorld::~CWorld() {
	// TODO Auto-generated destructor stub
}

void CWorld::draw(sf::RenderWindow* window) {

	for (std::vector<CEntity*>::iterator it = entities.begin(); it != entities.end();
			) {
		(*it)->draw(window);
	}

}

void CWorld::update(sf::Event event) {
	for (std::vector<CEntity*>::iterator it = entities.begin();
			it != entities.end();) {
		(*it)->update();
	}

}
