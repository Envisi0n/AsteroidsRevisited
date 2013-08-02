/*
 * CWorld.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#ifndef CWORLD_HPP_
#define CWORLD_HPP_

#include "../shared/World.hpp"
#include "CEntity.hpp"
#include <vector>

class CWorld: public World {
public:
	CWorld();
	virtual ~CWorld();
	void draw(sf::RenderWindow* window);
	void update(sf::Event event);
private:
	std::vector<CEntity*> entities;
};

#endif /* CWORLD_HPP_ */
