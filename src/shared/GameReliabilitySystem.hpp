/*
 * GameReliabilitySystem.hpp
 *
 *  Created on: Aug 19, 2013
 *      Author: Cam
 *      Credit: http://gafferongames.com/networking-for-game-programmers/reliability-and-flow-control/
 */

#ifndef GAMERELIABILITYSYSTEM_HPP_
#define GAMERELIABILITYSYSTEM_HPP_

#include "GamePacketQueue.hpp"
#include <vector>
#include <stdio.h>
#include <string>

class GameReliabilitySystem {
public:

	GameReliabilitySystem(unsigned int max_sequence = 0xFFFFFFFF);

	void Reset();

	void PacketSent(int size);

	void PacketReceived(unsigned int sequence, int size);

	unsigned int GenerateAckBits();

	void ProcessAck(unsigned int ack, unsigned int ack_bits);

	void Update(float deltaTime);

	void Validate();

	std::string toString();

	// utility functions

	static bool sequence_more_recent(unsigned int s1, unsigned int s2,
			unsigned int max_sequence);

	static int bit_index_for_sequence(unsigned int sequence, unsigned int ack,
			unsigned int max_sequence);

	static unsigned int generate_ack_bits(unsigned int ack,
			const GamePacketQueue & received_queue, unsigned int max_sequence);

	static void process_ack(unsigned int ack, unsigned int ack_bits,
			GamePacketQueue & pending_ack_queue, GamePacketQueue & acked_queue,
			std::vector<unsigned int> & acks, unsigned int & acked_packets,
			float & rtt, unsigned int max_sequence);

	// data accessors

	unsigned int GetLocalSequence() const;

	unsigned int GetRemoteSequence() const;

	unsigned int GetMaxSequence() const;
	void GetAcks(unsigned int ** acks, int & count);

	unsigned int GetSentPackets() const;

	unsigned int GetReceivedPackets() const;

	unsigned int GetLostPackets() const;

	unsigned int GetAckedPackets() const;

	float GetSentBandwidth() const;

	float GetAckedBandwidth() const;

	float GetRoundTripTime() const;

	int GetHeaderSize() const;

	float getLoss() const;

protected:

	void AdvanceQueueTime(float deltaTime);

	void UpdateQueues();

	void UpdateStats();

private:

	unsigned int max_sequence; // maximum sequence value before wrap around (used to test sequence wrap at low # values)
	unsigned int local_sequence; // local sequence number for most recently sent packet
	unsigned int remote_sequence; // remote sequence number for most recently received packet

	unsigned int sent_packets;			// total number of packets sent
	unsigned int recv_packets;			// total number of packets received
	unsigned int lost_packets;			// total number of packets lost
	unsigned int acked_packets;			// total number of packets acked

	float sent_bandwidth;	// approximate sent bandwidth over the last second
	float acked_bandwidth;	// approximate acked bandwidth over the last second
	float rtt;							// estimated round trip time
	float rtt_maximum;// maximum expected round trip time (hard coded to one second for the moment)

	std::vector<unsigned int> acks;	// acked packets from last set of packet receives. cleared each update!

	GamePacketQueue sentQueue;// sent packets used to calculate sent bandwidth (kept until rtt_maximum)
	GamePacketQueue pendingAckQueue;// sent packets which have not been acked yet (kept until rtt_maximum * 2 )
	GamePacketQueue receivedQueue;// received packets for determining acks to send (kept up to most recent recv sequence - 32)
	GamePacketQueue ackedQueue;	// acked packets (kept until rtt_maximum * 2)
};

#endif /* GAMERELIABILITYSYSTEM_HPP_ */
