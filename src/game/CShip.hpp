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

	virtual void setPosition(float x, float y);
	void setTexture(sf::Texture *texture);
	void draw(sf::RenderWindow* window);

private:
	sf::Sprite sprite;
};

#endif /* CSHIP_HPP_ */
