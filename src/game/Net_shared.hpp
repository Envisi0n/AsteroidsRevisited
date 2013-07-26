/*
 * Net_shared.hpp
 *
 *  Created on: Jul 11, 2013
 *      Author: cameron
 */

#ifndef NET_SHARED_HPP_
#define NET_SHARED_HPP_
#include <SFML/Network.hpp>
#define SERVER_PORT 30000

enum PacketTypes{

	CONNECT,
	GAMELOGIN,
	DISCONNECT,
	CLIENT_UPDATE,
	SERVER_UPDATE,

};


struct connectPacket {
	short packetType;

};

struct loginPacket {
	short packetType;
	char username[32];
	char password[32];
};



sf::Packet& operator <<(sf::Packet& packet, const connectPacket& connect);
sf::Packet& operator >>(sf::Packet& packet, connectPacket& connect);

sf::Packet& operator <<(sf::Packet& packet, const loginPacket& login);
sf::Packet& operator >>(sf::Packet& packet, loginPacket& login);



#endif /* NET_SHARED_HPP_ */
