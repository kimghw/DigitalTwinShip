#pragma once

#include "Protocol.pb.h"


// PacketHandlerFunc will be managed by the 'vector' but map could be used as well.
// First, input and output parameters are defined.
// Second, the HandlePacket function is defined which will be used to handle the packet
// the input parameter 'buffer' and 'len' will be used to parse the packet and provide the Array of the packet session.
// 
// 
using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

// The following enum will be used to define the packet id and index of the PacketHandlerFunc array.
enum : uint16
{
	H_LOGIN = 1000,
	H_TEST = 1001,
	H_PVImage = 1002,
	H_PVIntrinsic = 1003,
	H_PVExtrinsic = 1004,
	S_LOGIN = 2000,
	S_TEST = 2001,
};


// Where is packet handlers defined? in class? or out of class?

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_H_TEST(PacketSessionRef& session, Protocol::H_TEST& pkt);
bool Handle_S_TEST(PacketSessionRef& session, Protocol::S_TEST& pkt);
bool Handle_H_LOGIN(PacketSessionRef& session, Protocol::H_LOGIN& pkt);
bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt);



class ServerPacketHandler
{
	// First, Initialize the PacketHandlerFunc array.
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;

		// If the buffer arrives and the packet id is extracted, 
		// it will be used to call the corresponding function.
		GPacketHandler[S_TEST] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_TEST>(Handle_S_TEST, session, buffer, len); };
		GPacketHandler[H_TEST] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::H_TEST>(Handle_H_TEST, session, buffer, len); };
		GPacketHandler[H_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::H_LOGIN>(Handle_H_LOGIN, session, buffer, len); };
		GPacketHandler[S_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_LOGIN>(Handle_S_LOGIN, session, buffer, len); };

	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}

	static SendBufferRef MakeSendBuffer(Protocol::H_TEST pkt) { return MakeSendBuffer(pkt, H_TEST); }
	static SendBufferRef MakeSendBuffer(Protocol::H_LOGIN pkt) { return MakeSendBuffer(pkt, H_LOGIN); }


private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketType pkt;

		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, pkt);
	}

	template<typename T>
	static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
	{
		uint16 datasize = static_cast<uint16>(pkt.ByteSizeLong());
		uint16 packetSize = datasize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);

		// Insert the packet header into the sendBuffer
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;

		// Insert the packet body into the sendBuffer
		ASSERT_CRASH(pkt.SerializeToArray(&header[1], datasize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}

};

#pragma pack(1)



#pragma pack()