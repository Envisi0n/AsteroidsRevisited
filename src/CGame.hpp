/*
 * CGame.hpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#ifndef CGAME_HPP_
#define CGAME_HPP_

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

	sf::RectangleShape background;
	sf::Texture backgroundImage;
	int state;
	sf::RenderWindow window;

};

#endif /* CGAME_HPP_ */
