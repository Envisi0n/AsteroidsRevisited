/*
 * Button.hpp
 *
 *  Created on: May 11, 2013
 *      Author: David Jelley
 */

#ifndef Button_HPP_
#define Button_HPP_

#include <SFML/Graphics.hpp>

class Button {
public:
	Button(float x, float y, const char* path);
	virtual ~Button();

	virtual void draw(sf::RenderWindow* window);

private:
	sf::Sprite sprite;
	sf::Texture texture;

};

#endif /* Button_HPP_ */
