#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return true;
}


bool Handle_S_TEST(PacketSessionRef& session, Protocol::S_TEST& pkt)
{
	//std::cout << pkt.id() << " : " << pkt.player() << std::endl;
	return true;
}

bool Handle_S_MAIN(PacketSessionRef& session, Protocol::S_MAIN& pkt)
{
	return true;
}