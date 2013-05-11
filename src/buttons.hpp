/*
 * buttons.hpp
 *
 *  Created on: May 11, 2013
 *      Author: David Jelley
 */

#ifndef BUTTONS_HPP_
#define BUTTONS_HPP_

#include <SFML/Graphics.hpp>

class Buttons {
public:
	Buttons(int height, int width, char* path, int x, int y);
	virtual ~Buttons();

	virtual void draw(sf::RenderWindow* window);

private:
	sf::Sprite sprite;
	sf::Texture texture;

};

#endif /* BUTTONS_HPP_ */
