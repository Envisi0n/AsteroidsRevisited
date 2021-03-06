/*
 * GameReliabilitySystem.cpp
 *
 *  Created on: Aug 19, 2013
 *      Author: Cam
 */

#include "GameReliabilitySystem.hpp"
#include <sstream>

GameReliabilitySystem::GameReliabilitySystem(unsigned int max_sequence) {
	this->rtt_maximum = rtt_maximum;
	this->max_sequence = max_sequence;
	Reset();
}

void GameReliabilitySystem::Reset() {
	local_sequence = 0;
	remote_sequence = 0;
	sentQueue.clear();
	receivedQueue.clear();
	pendingAckQueue.clear();
	ackedQueue.clear();
	sent_packets = 0;
	recv_packets = 0;
	lost_packets = 0;
	acked_packets = 0;
	sent_bandwidth = 0.0f;
	acked_bandwidth = 0.0f;
	rtt = 0.0f;
	rtt_maximum = 1.0f;
}

void GameReliabilitySystem::PacketSent(int size) {
	if (sentQueue.exists(local_sequence)) {
		printf("local sequence %d exists\n", local_sequence);
		for (GamePacketQueue::iterator itor = sentQueue.begin();
				itor != sentQueue.end(); ++itor)
			printf(" + %d\n", itor->sequence);
	}
	assert(!sentQueue.exists(local_sequence));
	assert(!pendingAckQueue.exists(local_sequence));
	PacketData data;
	data.sequence = local_sequence;
	data.time = 0.0f;
	data.size = size;
	sentQueue.push_back(data);
	pendingAckQueue.push_back(data);
	sent_packets++;
	local_sequence++;
	if (local_sequence > max_sequence)
		local_sequence = 0;
}

void GameReliabilitySystem::PacketReceived(unsigned int sequence, int size) {
	recv_packets++;
	if (receivedQueue.exists(sequence))
		return;
	PacketData data;
	data.sequence = sequence;
	data.time = 0.0f;
	data.size = size;
	receivedQueue.push_back(data);
	if (sequence_more_recent(sequence, remote_sequence, max_sequence))
		remote_sequence = sequence;
}

unsigned int GameReliabilitySystem::GenerateAckBits() {
	return generate_ack_bits(GetRemoteSequence(), receivedQueue, max_sequence);
}

void GameReliabilitySystem::ProcessAck(unsigned int ack,
		unsigned int ack_bits) {
	process_ack(ack, ack_bits, pendingAckQueue, ackedQueue, acks, acked_packets,
			rtt, max_sequence);
}

void GameReliabilitySystem::Update(float deltaTime) {
	acks.clear();
	AdvanceQueueTime(deltaTime);
	UpdateQueues();
	UpdateStats();
#ifdef NET_UNIT_TEST
	Validate();
#endif
}

void GameReliabilitySystem::Validate() {
	sentQueue.verify_sorted(max_sequence);
	receivedQueue.verify_sorted(max_sequence);
	pendingAckQueue.verify_sorted(max_sequence);
	ackedQueue.verify_sorted(max_sequence);
}

// utility functions

bool GameReliabilitySystem::sequence_more_recent(unsigned int s1,
		unsigned int s2, unsigned int max_sequence) {
	return (s1 > s2)
			&& ((s1 - s2 <= max_sequence / 2)
					|| ((s2 > s1) && (s2 - s1 > max_sequence / 2)));
}

int GameReliabilitySystem::bit_index_for_sequence(unsigned int sequence,
		unsigned int ack, unsigned int max_sequence) {
	assert(sequence != ack);
	assert(!sequence_more_recent(sequence, ack, max_sequence));
	if (sequence > ack) {
		assert(ack < 33);
		assert(max_sequence >= sequence);
		return ack + (max_sequence - sequence);
	} else {
		assert(ack >= 1);
		assert(sequence <= ack - 1);
		return ack - 1 - sequence;
	}
}

unsigned int GameReliabilitySystem::generate_ack_bits(unsigned int ack,
		const GamePacketQueue & received_queue, unsigned int max_sequence) {
	unsigned int ack_bits = 0;
	for (GamePacketQueue::const_iterator itor = received_queue.begin();
			itor != received_queue.end(); itor++) {
		if (itor->sequence == ack
				|| sequence_more_recent(itor->sequence, ack, max_sequence))
			break;
		int bit_index = bit_index_for_sequence(itor->sequence, ack,
				max_sequence);
		if (bit_index <= 31)
			ack_bits |= 1 << bit_index;
	}
	return ack_bits;
}

void GameReliabilitySystem::process_ack(unsigned int ack, unsigned int ack_bits,
		GamePacketQueue & pending_ack_queue, GamePacketQueue & acked_queue,
		std::vector<unsigned int> & acks, unsigned int & acked_packets,
		float & rtt, unsigned int max_sequence) {
	if (pending_ack_queue.empty())
		return;

	GamePacketQueue::iterator itor = pending_ack_queue.begin();
	while (itor != pending_ack_queue.end()) {
		bool acked = false;

		if (itor->sequence == ack) {
			acked = true;
		} else if (!sequence_more_recent(itor->sequence, ack, max_sequence)) {
			int bit_index = bit_index_for_sequence(itor->sequence, ack,
					max_sequence);
			if (bit_index <= 31)
				acked = (ack_bits >> bit_index) & 1;
		}

		if (acked) {
			rtt += (itor->time - rtt) * 0.1f;

			acked_queue.insert_sorted(*itor, max_sequence);
			acks.push_back(itor->sequence);
			acked_packets++;
			itor = pending_ack_queue.erase(itor);
		} else
			++itor;
	}
}

// data accessors

unsigned int GameReliabilitySystem::GetLocalSequence() const {
	return local_sequence;
}

unsigned int GameReliabilitySystem::GetRemoteSequence() const {
	return remote_sequence;
}

unsigned int GameReliabilitySystem::GetMaxSequence() const {
	return max_sequence;
}

void GameReliabilitySystem::GetAcks(unsigned int ** acks, int & count) {
	*acks = &this->acks[0];
	count = (int) this->acks.size();
}

unsigned int GameReliabilitySystem::GetSentPackets() const {
	return sent_packets;
}

unsigned int GameReliabilitySystem::GetReceivedPackets() const {
	return recv_packets;
}

unsigned int GameReliabilitySystem::GetLostPackets() const {
	return lost_packets;
}

unsigned int GameReliabilitySystem::GetAckedPackets() const {
	return acked_packets;
}

float GameReliabilitySystem::GetSentBandwidth() const {
	return sent_bandwidth;
}

float GameReliabilitySystem::GetAckedBandwidth() const {
	return acked_bandwidth;
}

float GameReliabilitySystem::GetRoundTripTime() const {
	return rtt;
}

int GameReliabilitySystem::GetHeaderSize() const {
	return 12;
}

void GameReliabilitySystem::AdvanceQueueTime(float deltaTime) {
	for (GamePacketQueue::iterator itor = sentQueue.begin();
			itor != sentQueue.end(); itor++)
		itor->time += deltaTime;

	for (GamePacketQueue::iterator itor = receivedQueue.begin();
			itor != receivedQueue.end(); itor++)
		itor->time += deltaTime;

	for (GamePacketQueue::iterator itor = pendingAckQueue.begin();
			itor != pendingAckQueue.end(); itor++)
		itor->time += deltaTime;

	for (GamePacketQueue::iterator itor = ackedQueue.begin();
			itor != ackedQueue.end(); itor++)
		itor->time += deltaTime;
}

void GameReliabilitySystem::UpdateQueues() {
	const float epsilon = 0.001f;

	while (sentQueue.size() && sentQueue.front().time > rtt_maximum + epsilon)
		sentQueue.pop_front();

	if (receivedQueue.size()) {
		const unsigned int latest_sequence = receivedQueue.back().sequence;
		const unsigned int minimum_sequence =
				latest_sequence >= 34 ?
						(latest_sequence - 34) :
						max_sequence - (34 - latest_sequence);
		while (receivedQueue.size()
				&& !sequence_more_recent(receivedQueue.front().sequence,
						minimum_sequence, max_sequence))
			receivedQueue.pop_front();
	}

	while (ackedQueue.size()
			&& ackedQueue.front().time > rtt_maximum * 2 - epsilon)
		ackedQueue.pop_front();

	while (pendingAckQueue.size()
			&& pendingAckQueue.front().time > rtt_maximum + epsilon) {
		pendingAckQueue.pop_front();
		lost_packets++;
	}
}

std::string GameReliabilitySystem::toString() {

	std::stringstream tmp;

	tmp << "rtt " << rtt * 1000.0f << "ms, ";
	tmp << "sent " << sent_packets << ", ";
	tmp << "acked " << acked_packets << ",";
	tmp << "lost " << lost_packets << "(" << (sent_packets > 0.0f ?
			(float) lost_packets / (float) sent_packets * 100.0f :
			0.0f) << "%), ";
	tmp << "sent bandwidth " << sent_bandwidth << " kbps ";
	tmp << "acked bandwidth " << acked_bandwidth << " kbps";

	return tmp.str();

}

void GameReliabilitySystem::UpdateStats() {
	int sent_bytes_per_second = 0;
	for (GamePacketQueue::iterator itor = sentQueue.begin();
			itor != sentQueue.end(); ++itor)
		sent_bytes_per_second += itor->size;
	int acked_packets_per_second = 0;
	int acked_bytes_per_second = 0;
	for (GamePacketQueue::iterator itor = ackedQueue.begin();
			itor != ackedQueue.end(); ++itor) {
		if (itor->time >= rtt_maximum) {
			acked_packets_per_second++;
			acked_bytes_per_second += itor->size;
		}
	}
	sent_bytes_per_second /= rtt_maximum;
	acked_bytes_per_second /= rtt_maximum;
	sent_bandwidth = sent_bytes_per_second * (8 / 1000.0f);
	acked_bandwidth = acked_bytes_per_second * (8 / 1000.0f);
}

float GameReliabilitySystem::getLoss() const {
	return (float) lost_packets / (float) sent_packets * 100.0f;
}
