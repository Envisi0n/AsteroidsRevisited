/*
 * Net_shared.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: cameron
 */
#include "Net_shared.hpp"

sf::Packet& operator <<(sf::Packet& packet, const connectPacket& connect) {
	return packet << connect.packetType;
}

sf::Packet& operator >>(sf::Packet& packet, connectPacket& connect) {
	return packet >> connect.packetType;
}

sf::Packet& operator <<(sf::Packet& packet, const loginPacket& login) {
	return packet << login.packetType << login.username << login.password;
}

sf::Packet& operator >>(sf::Packet& packet, loginPacket& login) {
	return packet >> login.packetType << login.username >> login.password;
}
