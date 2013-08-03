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
#include "TextureManager.hpp"

enum gameState {

	INIT, MENU, LOGIN, PLAYING, PAUSE, QUIT

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
	TextureManager textureHandler;


};

#endif /* CGAME_HPP_ */
