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

class ClientEntity: public Entity {
public:
	ClientEntity();
	virtual ~ClientEntity();

	void draw(sf::RenderWindow* window);

private:
	sf::Sprite sprite;
	sf::Texture texture;
};

#endif /* CLIENTENTITY_HPP_ */
