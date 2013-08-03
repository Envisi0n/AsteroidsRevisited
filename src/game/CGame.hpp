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
#include "../shared/Net_shared.hpp"
#include "CWorld.hpp"
#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>

enum gameState {

	INIT, MENU, LOGIN, PLAYING, PAUSE, QUIT

};


extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
#define FRAMES_PER_SECOND 60

class CGame {
public:
	CGame();
	virtual ~CGame();

	virtual void init();
	virtual void run();
	virtual void draw(sf::RenderWindow* window);
	virtual void update();

	virtual void receiveServerUpdate();

	void showMenu();

	int getState() const;
	void setState(int state);

private:

	void handleButton(int action);
	void login();
	void gameRegister();
	// Background drawable object
	sf::RectangleShape background;
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

	// Asteroids game
	CWorld gameWorld;

	//Texture manager
	ResourceManager ResourceHandler;


};

#endif /* CGAME_HPP_ */
