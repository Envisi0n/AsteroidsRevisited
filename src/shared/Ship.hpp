/*
 * Ship.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#ifndef SHIP_HPP_
#define SHIP_HPP_

#include "Entity.hpp"

class Ship: public Entity {
public:
	Ship();
	Ship(float x, float y);
	virtual ~Ship();
private:
	float rotation;
};

#endif /* SHIP_HPP_ */
