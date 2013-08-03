/*
 * Menu.hpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include "Button.hpp"
#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#define CLICK_DELAY 0.1

using namespace std;

class Menu {
public:
	Menu();
	virtual ~Menu();

	virtual void draw(sf::RenderWindow* window);
	virtual int update(sf::Vector2f mouseLoc, sf::Event event);
	virtual void addButton(float x, float y, sf::Texture* texture, int action);
	virtual void addTextBox(float x, float y, sf::Font* font, float pWidth);
	const vector<TextBox*>& getTextBoxes() const;

private:
	// Holds all the buttons
	vector<Button*> buttons;

	// Holds all the textboxes
	vector<TextBox*> TextBoxes;

	// Timer
	static sf::Clock reset;
};

#endif /* MENU_HPP_ */
