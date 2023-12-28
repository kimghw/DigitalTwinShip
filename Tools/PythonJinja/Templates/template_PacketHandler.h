#pragma once
{%- for package in packages%}
#include "{{package['package']}}.pb.h"
{%- endfor %}
#include "enum.pb.h"
#include "pch.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
// R02 : 
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

// Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
// Called upon the reception of the source data to process it
{%- for package in packages %}
bool Handle_{{package['package']}}(PacketSessionRef& session, BYTE* buffer, int32 len);
{%- endfor %}
// Called when process partial data which are tables
{%- for package in packages%} 
{%- for table in package.tables%}
bool Handle_{{table['table_name']}}(PacketSessionRef& session, {{package['package']}}::{{table['table_name']}}& pkt);
{%- endfor %}
{% endfor %}

class {{type}}PacketHandler
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
		
{%- for package in packages%}
{%- for table in package.tables%}
		GPacketHandler[{{package['enumNameSpace']}}::{{table['table_name']}}] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<{{package['package']}}::{{table['table_name']}}>(Handle_{{table['table_name']}}, session, buffer, len); };
{%- endfor %}
{%- endfor %}
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
	{% for package in packages%}
{% for table in package.tables%}
	static SendBufferRef MakeSendBuffer({{package['package']}}::{{table['table_name']}}& pkt) { return MakeSendBuffer(pkt, static_cast<uint16>({{package['enumNameSpace']}}::{{table['table_name']}})); }
{%- endfor%}
{%- endfor%}

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
