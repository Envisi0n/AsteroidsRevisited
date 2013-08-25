/*
 * CShip.hpp
 *
 *  Created on: Aug 9, 2013
 *      Author: Cam
 */

#ifndef CSHIP_HPP_
#define CSHIP_HPP_

#include "../shared/Ship.hpp"
#include <SFML/Graphics.hpp>

class CShip: public Ship {
public:
	CShip();
	CShip(float x, float y, float velX, float velY, float rotation, sf::Texture *texture);
	virtual ~CShip();

	// Used by network updates
	virtual void update(float x, float y, float rotation);
	// Sets the texture of ship sprite
	void setTexture(sf::Texture *texture);
	// Draws the ship (interpolated position, rotation etc)
	void draw(sf::RenderWindow* window, float interpolation);

private:
	// Graphics of the sprite
	sf::Sprite sprite;
};

#endif /* CSHIP_HPP_ */
