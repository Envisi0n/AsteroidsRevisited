/*
 * CWorld.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#ifndef CWORLD_HPP_
#define CWORLD_HPP_

#include "../shared/World.hpp"
#include "CEntity.hpp"
#include "CPlayer.hpp"
#include <vector>

class CWorld: public World {
public:
	CWorld();
	virtual ~CWorld();
	void draw(sf::RenderWindow* window);
	void update(sf::Event event);
	void packetToWorld(sf::Packet packet);
	void handleEntityPacket(sf::Packet *packet);
private:
	std::vector<CEntity*> centities;
	std::vector<CPlayer*> cplayers;
};

#endif /* CWORLD_HPP_ */
