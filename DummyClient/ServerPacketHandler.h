#pragma once
#include "Protocol.pb.h"
#include "EDT0001.pb.h"
#include "pch.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
	PKT_TEST = 1000,
	PKT_EDT0001 = 1001,
	PKT_Battery = 1000,
	PKT_Battery_Pack = 1002,
	PKT_BAT_MODULE_0 = 1003,
	PKT_BAT_MODULE_1 = 1004,
	PKT_BAT_MODULE_2 = 1005,
	PKT_BAT_MODULE_3 = 1006,
	PKT_Environment = 1007,
	PKT_AIS = 1008,
	PKT_System_Time = 1009,
	PKT_MOTOR = 1010,
	PKT_INVERTER = 1011
};

// Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_EDT0001(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_Battery(PacketSessionRef& session, Protocol::Battery& pkt);
bool Handle_Battery_Pack(PacketSessionRef& session, Protocol::Battery_Pack& pkt);
bool Handle_BAT_MODULE_0(PacketSessionRef& session, Protocol::BAT_MODULE_0& pkt);
bool Handle_BAT_MODULE_1(PacketSessionRef& session, Protocol::BAT_MODULE_1& pkt);
bool Handle_BAT_MODULE_2(PacketSessionRef& session, Protocol::BAT_MODULE_2& pkt);
bool Handle_BAT_MODULE_3(PacketSessionRef& session, Protocol::BAT_MODULE_3& pkt);
bool Handle_Environment(PacketSessionRef& session, Protocol::Environment& pkt);
bool Handle_AIS(PacketSessionRef& session, Protocol::AIS& pkt);
bool Handle_System_Time(PacketSessionRef& session, Protocol::System_Time& pkt);
bool Handle_MOTOR(PacketSessionRef& session, Protocol::MOTOR& pkt);
bool Handle_INVERTER(PacketSessionRef& session, Protocol::INVERTER& pkt);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;

		//JSon
		GPacketHandler[PKT_EDT0001] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return Handle_EDT0001(session, buffer, len); };
		

		GPacketHandler[PKT_Battery] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::Battery >(Handle_Battery, session, buffer, len); };
		GPacketHandler[PKT_Battery_Pack] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::Battery_Pack >(Handle_Battery_Pack, session, buffer, len); };
		GPacketHandler[PKT_BAT_MODULE_0] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::BAT_MODULE_0 >(Handle_BAT_MODULE_0, session, buffer, len); };
		GPacketHandler[PKT_BAT_MODULE_1] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::BAT_MODULE_1 >(Handle_BAT_MODULE_1, session, buffer, len); };
		GPacketHandler[PKT_BAT_MODULE_2] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::BAT_MODULE_2 >(Handle_BAT_MODULE_2, session, buffer, len); };
		GPacketHandler[PKT_BAT_MODULE_3] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::BAT_MODULE_3 >(Handle_BAT_MODULE_3, session, buffer, len); };
		GPacketHandler[PKT_Environment] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::Environment >(Handle_Environment, session, buffer, len); };
		GPacketHandler[PKT_AIS] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::AIS >(Handle_AIS, session, buffer, len); };
		GPacketHandler[PKT_System_Time] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::System_Time >(Handle_System_Time, session, buffer, len); };
		GPacketHandler[PKT_MOTOR] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::MOTOR >(Handle_MOTOR, session, buffer, len); };
		GPacketHandler[PKT_INVERTER] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::INVERTER >(Handle_INVERTER, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}

	//Send
	static SendBufferRef MakeSendBuffer(const char* json_string) { return MakeSendBuffer(json_string, PKT_EDT0001); }
	static SendBufferRef MakeSendBuffer(Protocol::Battery& pkt) { return MakeSendBuffer(pkt, PKT_Battery); }
	static SendBufferRef MakeSendBuffer(Protocol::Battery_Pack& pkt) { return MakeSendBuffer(pkt, PKT_Battery_Pack); }
	static SendBufferRef MakeSendBuffer(Protocol::BAT_MODULE_0& pkt) { return MakeSendBuffer(pkt, PKT_BAT_MODULE_0); }
	static SendBufferRef MakeSendBuffer(Protocol::BAT_MODULE_1& pkt) { return MakeSendBuffer(pkt, PKT_BAT_MODULE_1); }
	static SendBufferRef MakeSendBuffer(Protocol::BAT_MODULE_2& pkt) { return MakeSendBuffer(pkt, PKT_BAT_MODULE_2); }
	static SendBufferRef MakeSendBuffer(Protocol::BAT_MODULE_3& pkt) { return MakeSendBuffer(pkt, PKT_BAT_MODULE_3); }
	static SendBufferRef MakeSendBuffer(Protocol::Environment& pkt) { return MakeSendBuffer(pkt, PKT_Environment); }
	static SendBufferRef MakeSendBuffer(Protocol::AIS& pkt) { return MakeSendBuffer(pkt, PKT_AIS); }
	static SendBufferRef MakeSendBuffer(Protocol::System_Time& pkt) { return MakeSendBuffer(pkt, PKT_System_Time); }
	static SendBufferRef MakeSendBuffer(Protocol::MOTOR& pkt) { return MakeSendBuffer(pkt, PKT_MOTOR); }
	static SendBufferRef MakeSendBuffer(Protocol::INVERTER& pkt) { return MakeSendBuffer(pkt, PKT_INVERTER); }
	
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
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}

	//json
	template<typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
	{

		return func(session, buffer + sizeof(PacketHeader), len);
	}

	//json
	static SendBufferRef  MakeSendBuffer(const char* json_string, uint16 pktId)
	{
		cout << std::strlen(json_string) << endl;
		const uint16 dataSize = static_cast<uint16>(std::strlen(json_string));
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
		//cout << sizeof(sendBuffer) << endl;
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = 0;

		//char* header1 = reinterpret_cast<char*>(sendBuffer->Buffer());
		//std::swap(*header1, *(header1 + 1));
		//std::swap(*(header1 + 2), *(header1 + 3));


		ASSERT_CRASH(std::memcpy(reinterpret_cast<BYTE*>(&header[1]), json_string, dataSize));
		sendBuffer->Close(packetSize);


		return sendBuffer;
	}
};