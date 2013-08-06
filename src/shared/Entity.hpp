/*
 * Entity.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

class Entity {
public:
	Entity();
	Entity(float x, float y);
	virtual ~Entity();

	virtual void update();

	float getX() const;
	void setX(float x);
	float getY() const;
	void setY(float y);
	float getVelX() const;
	void setVelX(float velX);
	float getVelY() const;
	void setVelY(float velY);

private:
	float x, y;
	float velX, velY;
};

#endif /* ENTITY_HPP_ */
