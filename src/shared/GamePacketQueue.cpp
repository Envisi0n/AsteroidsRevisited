/*
 * GamePacketQueue.cpp
 *
 *  Created on: Aug 19, 2013
 *      Author: Cam
 */

#include "GamePacketQueue.hpp"

bool GamePacketQueue::exists(unsigned int sequence) {
	for (iterator itor = begin(); itor != end(); ++itor)
		if (itor->sequence == sequence)
			return true;
	return false;
}

void GamePacketQueue::insert_sorted(const PacketData & p, unsigned int max_sequence) {
	if (empty()) {
		push_back(p);
	} else {
		if (!sequence_more_recent(p.sequence, front().sequence, max_sequence)) {
			push_front(p);
		} else if (sequence_more_recent(p.sequence, back().sequence,
				max_sequence)) {
			push_back(p);
		} else {
			for (GamePacketQueue::iterator itor = begin(); itor != end();
					itor++) {
				assert(itor->sequence != p.sequence);
				if (sequence_more_recent(itor->sequence, p.sequence,
						max_sequence)) {
					insert(itor, p);
					break;
				}
			}
		}
	}
}

void GamePacketQueue::verify_sorted(unsigned int max_sequence) {
	GamePacketQueue::iterator prev = end();
	for (GamePacketQueue::iterator itor = begin(); itor != end(); itor++) {
		assert(itor->sequence <= max_sequence);
		if (prev != end()) {
			assert(
					sequence_more_recent(itor->sequence, prev->sequence,
							max_sequence));
			prev = itor;
		}
	}
}

