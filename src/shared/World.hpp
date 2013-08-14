/*
 * World.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <vector>
#include "Entity.hpp"
#include "Player.hpp"
#include <SFML/Network.hpp>

enum WorldObjectTypes {
	ENTITY,
	PLAYER,
	ASTEROID,
};

class World {
public:
	World();
	virtual void update();
	virtual ~World();

	// Player functions
	void createPlayer( int client, std::string userName );
	void removePlayer( int client );
	void removePlayer( std::string userName);
	void updatePlayer( int client, sf::Packet updatePacket);

	void addEntity();

	sf::Packet toPacket();
private:

	std::vector<Entity*> entities;
	std::vector<Player*> players;
};

#endif /* WORLD_HPP_ */
