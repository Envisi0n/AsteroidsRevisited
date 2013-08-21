/*
 * GamePacketQueue.hpp
 *
 *  Created on: Aug 19, 2013
 *      Author: Cam
 *      Credit: http://gafferongames.com/networking-for-game-programmers/reliability-and-flow-control/
 */

#ifndef PACKETQUEUE_HPP_
#define PACKETQUEUE_HPP_

#include <list>
#include <assert.h>


using namespace std;

struct PacketData {
	unsigned int sequence;			// packet sequence number
	float time;	// time offset since packet was sent or received (depending on context)
	int size;						// packet size in bytes
};

inline bool sequence_more_recent(unsigned int s1, unsigned int s2,
		unsigned int max_sequence) {
	return ( ((s1 > s2) && (s1 - s2 <= max_sequence / 2)) || ((s2 > s1) && (s2 - s1 > max_sequence / 2)));
}

class GamePacketQueue: public std::list<PacketData> {
public:

	bool exists(unsigned int sequence);
	void insert_sorted(const PacketData & p, unsigned int max_sequence);
	void verify_sorted(unsigned int max_sequence);
};

#endif /* PACKETQUEUE_HPP_ */
