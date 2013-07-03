/*
 * Menu.hpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;

class Menu {
public:
	Menu();
	virtual ~Menu();

	virtual void draw(sf::RenderWindow* window);
	virtual void addButton(float x, float y, const char* path, void (*fun)());

private:

	vector<Button*> buttons;
};

#endif /* MENU_HPP_ */
