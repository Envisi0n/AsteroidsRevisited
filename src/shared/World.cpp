/*
 * World.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "World.hpp"

World::World() {
	// TODO Auto-generated constructor stub

}

void World::update() {

	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ) {

		(*it)->update();
	}

}

World::~World() {
	// TODO Auto-generated destructor stub
}

