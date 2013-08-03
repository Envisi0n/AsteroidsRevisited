/*
 * World.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <vector>
#include "Entity.hpp"
#include <SFML/Network.hpp>

class World {
public:
	World();
	virtual void update();
	virtual ~World();

	sf::Packet toPacket();
private:

	std::vector<Entity*> entities;
};

#endif /* WORLD_HPP_ */
