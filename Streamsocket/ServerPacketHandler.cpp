#include "ServerPacketHandler.h"


PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(ServiceRef& session, BYTE* buffer, int32 len)
{
	return true;
}

bool Handle_S_TEST(ServiceRef& session, Protocol::S_TEST& pkt)
{
	std::cout<< pkt.id() << " : " << pkt.player() << std::endl;

	return true;
}

