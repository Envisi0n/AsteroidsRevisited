/*
 * Player.hpp
 *
 *  Created on: Aug 4, 2013
 *      Author: Cam
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Ship.hpp"
#include <string>

class Player {
public:
	Player();
	Player(int clientID, std::string userName);
	virtual ~Player();

	// Extracts info into packet
	virtual void toPacket(sf::Packet *packet);
	// Imports info from packet
	virtual void fromPacket(sf::Packet *packet);
	virtual std::string toString();

	virtual void update();

	float getLastSeen() const;
	void setLastSeen(float lastSeen);
	float getPing() const;
	void setPing(float ping);
	int getClientId() const;
	void setClientId(int clientId);
	const std::string& getUserName() const;
	void setUserName(const std::string& userName);

private:
	int clientID;
	std::string userName;
	Ship ship;
	float lastSeen;
	float ping;
};

#endif /* PLAYER_HPP_ */
