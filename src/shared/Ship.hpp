/*
 * Ship.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#ifndef SHIP_HPP_
#define SHIP_HPP_

#include "Entity.hpp"

#define ACCELERATION .1
#define MAXSPEED 3

enum thrustDirections {
	FORWARD,
	REVERSE
};

enum turnDirections {
	LEFT,
	RIGHT
};

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

	virtual void clientUpdate( int clientAction );


	float getRotation() const;
	void setRotation(float rotation);

private:

	// Game functions
	virtual void thrust( int direction );
	virtual void turn( int direction );

	float rotation;
};

#endif /* SHIP_HPP_ */
