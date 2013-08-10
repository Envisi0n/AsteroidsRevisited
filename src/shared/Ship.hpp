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
	Ship(float x, float y, float velX, float velY, float rotation);
	virtual ~Ship();

	virtual void update();

	// Extracts info into packet
	virtual void toPacket(sf::Packet *packet);
	// Imports info from packet
	virtual void fromPacket(sf::Packet *packet);
	virtual std::string toString();

	float getRotation() const;
	void setRotation(float rotation);

private:
	float rotation;
};

#endif /* SHIP_HPP_ */
