/*
 * CPlayer.hpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Cam
 */

#ifndef CPLAYER_HPP_
#define CPLAYER_HPP_

#include "../shared/Player.hpp"
#include "CShip.hpp"

class CPlayer: public Player {
public:
	CPlayer();
	virtual ~CPlayer();

	void draw(sf::RenderWindow *window, float interpolation);

	virtual void fromPacket(sf::Packet *packet);

	void setShipTexture(sf::Texture *texture);
	void setShipPosition(float x, float y);
	unsigned int getShipID();
	float getShipX();
	float getShipY();
private:
	CShip clientShip;
};

#endif /* CPLAYER_HPP_ */
