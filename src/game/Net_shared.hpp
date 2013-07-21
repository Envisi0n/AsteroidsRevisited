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



sf::Packet& operator <<(sf::Packet& packet, const connectPacket& connect);
sf::Packet& operator >>(sf::Packet& packet, connectPacket& connect);




#endif /* NET_SHARED_HPP_ */
