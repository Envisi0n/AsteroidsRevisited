/*
 * Client.cpp
 *
 *  Created on: May 9, 2013
 *      Author: cam
 */

#include "Client.hpp"
#include <iostream>
#include "../shared/GameGlobals.hpp"

Client::Client() {

	connection.setRemotePort(SERVER_PORT);
	connection.Start(CLIENT_PORT);
}

Client::~Client() {
	// TODO Auto-generated destructor stub
}


sf::Socket::Status Client::send( sf::Packet data) {

	return connection.SendPacket(data);

}

void Client::Connect(sf::IpAddress ip) {

	connection.Connect(ip);

}

sf::Socket::Status Client::receive( sf::Packet *data) {

	return connection.ReceivePacket( data );
}
