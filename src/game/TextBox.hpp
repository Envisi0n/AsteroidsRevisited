/*
 * TextBox.hpp
 *
 *  Created on: Jul 25, 2013
 *      Author: Dave
 */

#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include <SFML/Graphics.hpp>
#include "CGame_shared.hpp"

class TextBox {
public:

	TextBox(float x, float y, float pWidth);
	virtual ~TextBox();

	// Game functions
	void draw(sf::RenderWindow* window);
	//int update(sf::Vector2i mouseLoc, sf::Event event);

	// Assessors
	void setPosition( float x, float y);
	void setSize(float pWidth);


private:

	// Drawable box
	sf::RectangleShape rectangle;

};

#endif /* TEXTBOX_H_ */
