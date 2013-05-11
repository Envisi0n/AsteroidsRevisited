/*
 * CGame.hpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#ifndef CGAME_HPP_
#define CGAME_HPP_

#include "Menu.hpp"

enum gameState{

	INIT,
	MENU,
	PLAYING,
	PAUSE,
	QUIT


};

#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class CGame {
public:
	CGame();
	virtual ~CGame();

	virtual void init();
	virtual void run();
	virtual void update();
	int getState() const;
	void setState(int state);

private:

	// Background drawable object
	sf::RectangleShape background;
	// Background texture
	sf::Texture backgroundImage;
	// State of the game
	int state;
	// Window of the game
	sf::RenderWindow window;
	// Game menu
	Menu gameMenu;


};

#endif /* CGAME_HPP_ */
