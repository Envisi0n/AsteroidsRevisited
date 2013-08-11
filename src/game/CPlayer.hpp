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

	void setShipTexture(sf::Texture *texture);
private:
	CShip ship;
};

#endif /* CPLAYER_HPP_ */
