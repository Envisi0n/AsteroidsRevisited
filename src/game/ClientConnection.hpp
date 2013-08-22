/*
 * Client.hpp
 *
 *  Created on: May 9, 2013
 *      Author: cam
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "../shared/GameConnection.hpp"

class ClientConnection {
public:
	ClientConnection();
	virtual ~ClientConnection();
	void Connect(sf::IpAddress ip);
	bool send( sf::Packet data );
	int receive( sf::Packet *data);
private:

	GameConnection connection;
};

#endif /* CLIENT_HPP_ */
