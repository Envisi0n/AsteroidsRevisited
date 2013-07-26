/*
 * Button.hpp
 *
 *  Created on: May 11, 2013
 *      Author: David Jelley
 */

#ifndef Button_HPP_
#define Button_HPP_

#include <SFML/Graphics.hpp>
#include "CGame_shared.hpp"

enum buttonColors {

	NORMAL,
	OVER,
	CLICK

};


class Button {
public:

	Button(float x, float y, const char* texturePath, int action);
	virtual ~Button();

	// Game functions
	void draw(sf::RenderWindow* window);
	int update(sf::Vector2i mouseLoc, sf::Event event);
	void animate(int color);

	// Accessors
	void setPosition( float x, float y);
	int getAction() const;
	void setAction(int action);

private:

	// Drawable button
	sf::Sprite sprite;
	// Texture of button
	sf::Texture texture;
	// What the buttons does when clicked
	int action;
};

#endif /* Button_HPP_ */
