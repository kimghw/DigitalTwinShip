#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return true;
}


bool Handle_S_TEST(PacketSessionRef& session, Protocol::S_TEST& pkt)
{
	pkt.test();
	
	return true;
}