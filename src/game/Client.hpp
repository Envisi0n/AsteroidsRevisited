/*
 * Client.hpp
 *
 *  Created on: May 9, 2013
 *      Author: cam
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "../shared/GameConnection.hpp"

class Client {
public:
	Client();
	virtual ~Client();
	void Connect(sf::IpAddress ip);
	sf::Socket::Status send( sf::Packet data );
	sf::Socket::Status receive( sf::Packet *data);
private:

	GameConnection connection;
};

#endif /* CLIENT_HPP_ */
