/*
 * Client.cpp
 *
 *  Created on: May 9, 2013
 *      Author: cam
 */

#include "ClientConnection.hpp"
#include "../shared/GameGlobals.hpp"

ClientConnection::ClientConnection() : connection(PROTOCOL,TIMEOUT) {

	connection.setRemotePort(SERVER_PORT);
	connection.Start();
}

ClientConnection::~ClientConnection() {
	// TODO Auto-generated destructor stub
}


bool ClientConnection::send( sf::Packet data) {

	return connection.SendPacket(data);

}

void ClientConnection::Connect(sf::IpAddress ip) {

	connection.Connect(ip);

}

int ClientConnection::receive( sf::Packet *data) {

	return connection.ReceivePacket( data );
}
