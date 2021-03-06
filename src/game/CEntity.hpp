/*
 * ClientEntity.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#ifndef CLIENTENTITY_HPP_
#define CLIENTENTITY_HPP_

#include <SFML/Graphics.hpp>

#include "../shared/Entity.hpp"

class CEntity: public Entity {
public:
	CEntity();
	CEntity(float x, float y, float velX, float velY);
	virtual ~CEntity();

	virtual void setPosition(float x, float y);

	virtual void draw(sf::RenderWindow* window, float interpolation);
	virtual void update(sf::Event event);

private:
	sf::Sprite sprite;
	sf::Texture texture;
};

#endif /* CLIENTENTITY_HPP_ */
