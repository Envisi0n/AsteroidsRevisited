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
#include <string>
#define TYPE_DELAY 125

class TextBox {
public:

	TextBox(float x, float y, sf::Font* font, float pWidth);
	virtual ~TextBox();

	// Game functions
	void draw(sf::RenderWindow* window);
	void update(sf::Vector2i mouseLoc, sf::Event event);

	// Assessors
	void setPosition( float x, float y);
	void setSize(float pWidth);

	bool getHasFocus() const;
	void setHasFocus(bool hasFocus);
	const sf::Text& getText() const;
	void setText(const sf::Text& text);

	std::string toString();

private:

	// Drawable box
	sf::RectangleShape rectangle;

	// Has focus?
	bool hasFocus;
	// Previous Event Tracker
	sf::Uint32 prevEvent;
	sf::Clock reset;
	
	// Text Field
	sf::Text Text;
	sf::Font font;
};

#endif /* TEXTBOX_H_ */
