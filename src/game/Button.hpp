/*
 * Button.hpp
 *
 *  Created on: May 11, 2013
 *      Author: David Jelley
 */

#ifndef Button_HPP_
#define Button_HPP_

#include <SFML/Graphics.hpp>
#include <functional>

enum buttonColors {

	NORMAL,
	OVER,
	CLICK

};


class Button {
public:

	Button(float x, float y, const char* texturePath, void (*fun)());
	virtual ~Button();

	// Game functions
	void draw(sf::RenderWindow* window);
	void update(sf::Vector2i mouseLoc);
	void runAction();
	void animate(int color);

	// Accessors
	void setPosition( float x, float y);


private:

	// Drawable button
	sf::Sprite sprite;
	// Texture of button
	sf::Texture texture;
	// What the buttons does when clicked
	void (*action)();
};

#endif /* Button_HPP_ */
