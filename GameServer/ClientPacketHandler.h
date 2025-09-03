#pragma once
#include "EDT0001.pb.h"
#include "MRSchema.pb.h"
#include "enum.pb.h"
#include "pch.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
// R02 : 
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

// Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
// Called upon the reception of the source data to process it
bool Handle_EDT0001(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_MRSchema(PacketSessionRef& session, BYTE* buffer, int32 len);
// Called when process partial data which are tables
bool Handle_Battery(PacketSessionRef& session, EDT0001::Battery& pkt);
bool Handle_Battery_Pack(PacketSessionRef& session, EDT0001::Battery_Pack& pkt);
bool Handle_BAT_MODULE_0(PacketSessionRef& session, EDT0001::BAT_MODULE_0& pkt);
bool Handle_BAT_MODULE_1(PacketSessionRef& session, EDT0001::BAT_MODULE_1& pkt);
bool Handle_BAT_MODULE_2(PacketSessionRef& session, EDT0001::BAT_MODULE_2& pkt);
bool Handle_BAT_MODULE_3(PacketSessionRef& session, EDT0001::BAT_MODULE_3& pkt);
bool Handle_Environment(PacketSessionRef& session, EDT0001::Environment& pkt);
bool Handle_AIS(PacketSessionRef& session, EDT0001::AIS& pkt);
bool Handle_System_Time(PacketSessionRef& session, EDT0001::System_Time& pkt);
bool Handle_MOTOR(PacketSessionRef& session, EDT0001::MOTOR& pkt);
bool Handle_INVERTER(PacketSessionRef& session, EDT0001::INVERTER& pkt);
bool Handle_Network(PacketSessionRef& session, EDT0001::Network& pkt);
bool Handle_SaveAsBytes(PacketSessionRef& session, EDT0001::SaveAsBytes& pkt);

bool Handle_C_Position(PacketSessionRef& session, MRSchema::C_Position& pkt);
bool Handle_XrCpuPlan(PacketSessionRef& session, MRSchema::XrCpuPlan& pkt);
bool Handle_XrCpuImage(PacketSessionRef& session, MRSchema::XrCpuImage& pkt);


class ClientPacketHandler
{
public:
	// R01 : the below function is called with received data from client at first time
	// Check the packet ID and call a handle function
	static bool HandleBuffer(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));
	}

	// R02 : One of a component among fuction vectors called from R01
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;

		//JSon
		GPacketHandler[1001] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return Handle_EDT0001(session, buffer, len); };
		GPacketHandler[EDT::Battery] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::Battery>(Handle_Battery, session, buffer, len); };
		GPacketHandler[EDT::Battery_Pack] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::Battery_Pack>(Handle_Battery_Pack, session, buffer, len); };
		GPacketHandler[EDT::BAT_MODULE_0] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::BAT_MODULE_0>(Handle_BAT_MODULE_0, session, buffer, len); };
		GPacketHandler[EDT::BAT_MODULE_1] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::BAT_MODULE_1>(Handle_BAT_MODULE_1, session, buffer, len); };
		GPacketHandler[EDT::BAT_MODULE_2] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::BAT_MODULE_2>(Handle_BAT_MODULE_2, session, buffer, len); };
		GPacketHandler[EDT::BAT_MODULE_3] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::BAT_MODULE_3>(Handle_BAT_MODULE_3, session, buffer, len); };
		GPacketHandler[EDT::Environment] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::Environment>(Handle_Environment, session, buffer, len); };
		GPacketHandler[EDT::AIS] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::AIS>(Handle_AIS, session, buffer, len); };
		GPacketHandler[EDT::System_Time] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::System_Time>(Handle_System_Time, session, buffer, len); };
		GPacketHandler[EDT::MOTOR] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::MOTOR>(Handle_MOTOR, session, buffer, len); };
		GPacketHandler[EDT::INVERTER] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::INVERTER>(Handle_INVERTER, session, buffer, len); };
		GPacketHandler[EDT::Network] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::Network>(Handle_Network, session, buffer, len); };
		GPacketHandler[EDT::SaveAsBytes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<EDT0001::SaveAsBytes>(Handle_SaveAsBytes, session, buffer, len); };
		GPacketHandler[EDT::C_Position] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<MRSchema::C_Position>(Handle_C_Position, session, buffer, len); };
		GPacketHandler[EDT::XrCpuPlan] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<MRSchema::XrCpuPlan>(Handle_XrCpuPlan, session, buffer, len); };
		GPacketHandler[EDT::XrCpuImage] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<MRSchema::XrCpuImage>(Handle_XrCpuImage, session, buffer, len); };
	}
	// R03 : After checking the packet type, 
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, pkt);
	}

	// j
	static SendBufferRef MakeSendBuffer(const char* json_string) { return MakeSendBuffer(json_string, 1001); }
	// S01 :This is an first procedure to send a message
	// the below function returns a function to make a buffer at first time 
	

	static SendBufferRef MakeSendBuffer(EDT0001::Battery& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::Battery)); }
	static SendBufferRef MakeSendBuffer(EDT0001::Battery_Pack& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::Battery_Pack)); }
	static SendBufferRef MakeSendBuffer(EDT0001::BAT_MODULE_0& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::BAT_MODULE_0)); }
	static SendBufferRef MakeSendBuffer(EDT0001::BAT_MODULE_1& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::BAT_MODULE_1)); }
	static SendBufferRef MakeSendBuffer(EDT0001::BAT_MODULE_2& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::BAT_MODULE_2)); }
	static SendBufferRef MakeSendBuffer(EDT0001::BAT_MODULE_3& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::BAT_MODULE_3)); }
	static SendBufferRef MakeSendBuffer(EDT0001::Environment& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::Environment)); }
	static SendBufferRef MakeSendBuffer(EDT0001::AIS& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::AIS)); }
	static SendBufferRef MakeSendBuffer(EDT0001::System_Time& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::System_Time)); }
	static SendBufferRef MakeSendBuffer(EDT0001::MOTOR& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::MOTOR)); }
	static SendBufferRef MakeSendBuffer(EDT0001::INVERTER& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::INVERTER)); }
	static SendBufferRef MakeSendBuffer(EDT0001::Network& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::Network)); }
	static SendBufferRef MakeSendBuffer(EDT0001::SaveAsBytes& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::SaveAsBytes)); }

	static SendBufferRef MakeSendBuffer(MRSchema::C_Position& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::C_Position)); }
	static SendBufferRef MakeSendBuffer(MRSchema::XrCpuPlan& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::XrCpuPlan)); }
	static SendBufferRef MakeSendBuffer(MRSchema::XrCpuImage& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>(EDT::XrCpuImage)); }

	// S02 : S01 Return the below fuction
	// This function received a packet buffer and returns a send buffer with a packet header appended
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
	//JR01:
	template<typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		return func(session, buffer + sizeof(PacketHeader), len);
	}

	//json
	//JS01:
	static SendBufferRef  MakeSendBuffer(const char* json_string, uint16 pktId)
	{
		cout << std::strlen(json_string) << endl;
		const uint16 dataSize = static_cast<uint16>(std::strlen(json_string));
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
		//cout << sizeof(sendBuffer) << endl;
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(std::memcpy(reinterpret_cast<BYTE*>(&header[1]), json_string, dataSize));
		sendBuffer->Close(packetSize);
		return sendBuffer;
	}
};