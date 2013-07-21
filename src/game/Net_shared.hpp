/*
 * Net_shared.hpp
 *
 *  Created on: Jul 11, 2013
 *      Author: cameron
 */

#ifndef NET_SHARED_HPP_
#define NET_SHARED_HPP_

#define SERVER_PORT 30000

enum PacketTypes{

	CONNECT,
	LOGIN,
	DISCONNECT,
	CLIENT_UPDATE,
	SERVER_UPDATE,

};


struct connectPacket {
	short packetType;

};


sf::Packet& operator <<(sf::Packet& packet, const connectPacket& connect)
{
    return packet << connect.packetType;
}

sf::Packet& operator >>(sf::Packet& packet, connectPacket& connect)
{
    return packet >> connect.packetType;
}





#endif /* NET_SHARED_HPP_ */
