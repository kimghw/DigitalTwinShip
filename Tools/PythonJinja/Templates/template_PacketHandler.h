#pragma once
#include "Protocol.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
	PKT_{{Ship_num}} = 1000,
{%- for table in tables%}
	PKT_{{table['table_name']}} = {{'%04d'|format(loop.index+1000)}}{%- if not loop.last-%},{%- endif-%}
{%- endfor %}
};

// Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_{{Ship_num}}(PacketSessionRef& session, BYTE* buffer, int32 len);

{%- for table in tables %}
bool Handle_{{table['table_name']}}(PacketSessionRef& session, Protocol::{{table['table_name']}}& pkt);
{%- endfor %}

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;

		//JSon
		GPacketHandler[PKT_{{Ship_num}}] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return Handle_EDT0001(Handle_Json, session, buffer, len); };
		
{% for table in tables %}
		GPacketHandler[PKT_{{table['table_name']}}] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::{{table['table_name']}} >(Handle_{{table['table_name']}}, session, buffer, len); };
{%- endfor %}
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}

	//Send
	static SendBufferRef MakeSendBuffer(const char* json_string) { return MakeSendBuffer(json_string, PKT_{{Ship_num}}); }
{%- for table in tables%}
	static SendBufferRef MakeSendBuffer(Protocol::{{table['table_name']}}& pkt) { return MakeSendBuffer(pkt, PKT_{{table['table_name']}}); }
{%- endfor %}
	
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
		header->id = pktId;
		ASSERT_CRASH(std::memcpy(reinterpret_cast<BYTE*>(&header[1]), json_string, dataSize));
		sendBuffer->Close(packetSize);


		return sendBuffer;
	}
};
