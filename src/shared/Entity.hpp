/*
 * Entity.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <string>
#include <SFML/Network.hpp>

class Entity {
public:
	Entity();
	Entity(float x, float y, float velX, float velY);
	virtual ~Entity();

	virtual void update();


	void toPacket(sf::Packet *packet);
	std::string toString();

	float getX() const;
	void setX(float x);
	float getY() const;
	void setY(float y);
	float getVelX() const;
	void setVelX(float velX);
	float getVelY() const;
	void setVelY(float velY);
	unsigned int getId() const;

private:
	static unsigned int nextID;
	unsigned int id;
	float x, y;
	float velX, velY;
};

#endif /* ENTITY_HPP_ */
