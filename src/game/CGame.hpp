/*
 * CGame.hpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#ifndef CGAME_HPP_
#define CGAME_HPP_

#include "Menu.hpp"
#include "CGame_shared.hpp"
#include "Client.hpp"
#include "Net_shared.hpp"

enum gameState {

	INIT, MENU, LOGIN, NETCONNECT, PLAYING, PAUSE, QUIT

};

#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FRAMES_PER_SECOND 60

class CGame {
public:
	CGame();
	virtual ~CGame();

	virtual void init();
	virtual void run();
	virtual void update();

	void showMenu();

	int getState() const;
	void setState(int state);

private:

	void handleButton(int action);
	void netConnect();
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
	// Window icon :D
	sf::Image icon;
	// Login menu
	Menu loginMenu;

	// Networking
	Client gameClient;


};

#endif /* CGAME_HPP_ */
