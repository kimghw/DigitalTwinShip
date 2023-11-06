#pragma once
#include "Protocol.pb.h"
#include "DBConnectionPool.h"
#include "DBBind.h"


using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];
void replaceDegrees(std::string& coord);
void addBackslashBeforeQuotes(OUT std::string& input);

enum : uint16
{
	PKT_S_TEST = 1000,
	PKT_C_TEST = 1111,
	PKT_C_MAIN = 1002,
	PKT_S_MAIN = 1003,

	PKT_C_JSON = 1001,
};

// Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_TEST(PacketSessionRef& session, Protocol::C_TEST& pkt);
//bool Handle_C_MAIN(PacketSessionRef& session, Protocol::C_TEST& pkt);
bool Handle_S_TEST(PacketSessionRef& session, Protocol::S_TEST& pkt);
bool Handle_S_MAIN(PacketSessionRef& session, Protocol::S_MAIN& pkt);

//json
bool Handle_Json(PacketSessionRef& session, BYTE* buffer, int32 len);
class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_C_TEST] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_TEST>(Handle_C_TEST, session, buffer, len); };
		//GPacketHandler[PKT_C_MAIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_MAIN>(Handle_C_MAIN, session, buffer, len); };
		GPacketHandler[PKT_S_MAIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_MAIN>(Handle_S_MAIN, session, buffer, len); };

		//JSon
		GPacketHandler[PKT_C_JSON] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket(Handle_Json, session, buffer, len); };

	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::C_TEST& pkt) { return MakeSendBuffer(pkt, PKT_C_TEST); }
	static SendBufferRef MakeSendBuffer(Protocol::C_MAIN& pkt) { return MakeSendBuffer(pkt, PKT_C_MAIN); }

	//json
	static SendBufferRef MakeSendBuffer(const char* json_string) { return MakeSendBuffer(json_string, PKT_C_JSON); }

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
	static SendBufferRef  MakeSendBuffer(T& pkt, uint16 pktId)
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

		return func(session, buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));
	}

	//json
	static SendBufferRef  MakeSendBuffer(const char* json_string, uint16 pktId)
	{
		//cout << std::strlen(json_string) << endl;
		const uint16 dataSize = static_cast<uint16>(std::strlen(json_string));
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
		//cout << sizeof(sendBuffer) << endl;
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(std::memcpy(reinterpret_cast<BYTE*>(&header[1]), json_string, dataSize));
		sendBuffer->Close(packetSize);

		std::cout << "recevied data in ClientPacketHandler 110lines" << endl;
		return sendBuffer;
	}
};