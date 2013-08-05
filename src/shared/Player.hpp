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
	Player(int clientID, std::string userName);
	virtual ~Player();
	int getClientId() const;
	void setClientId(int clientId);
	const std::string& getUserName() const;
	void setUserName(const std::string& userName);

private:
	int clientID;
	std::string userName;
	Ship ship;
};

#endif /* PLAYER_HPP_ */
