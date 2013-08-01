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

#define WORLD_HEIGHT 800
#define WORLD_WIDTH 600

class World {
public:
	World();
	virtual void update();
	virtual ~World();
private:

	std::vector<Entity*> entities;
};

#endif /* WORLD_HPP_ */
