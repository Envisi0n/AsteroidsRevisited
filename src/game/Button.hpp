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

	NORMAL, OVER, CLICK

};

class Button {
public:

	Button(float x, float y, sf::Texture* texture, int action);
	virtual ~Button();

	// Game functions
	void draw(sf::RenderWindow* window);
	int update(sf::Vector2f mouseLoc, sf::Event event);
	void animate(int color);

	// Assessors
	void setPosition(float x, float y);
	int getAction() const;
	void setAction(int action);
	bool isPressed() const;
	void setPressed(bool pressed);

private:

	// Drawable button
	sf::Sprite sprite;
	// What the buttons does when clicked
	int action;
	// Click flag
	bool pressed;
};

#endif /* Button_HPP_ */
