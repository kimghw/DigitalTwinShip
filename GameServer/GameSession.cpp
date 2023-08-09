#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"


void GameSession::OnConnected()
{
	GSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "Client is connected" << endl;

	Protocol::S_TEST pkt;
	pkt.set_id(1);
	pkt.set_player("G");
	
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt);

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Send size : "<< sizeof(sendBuffer) << std::endl;
		this->Send(sendBuffer);
		cout << "Send S_TEST : Successful" << endl;
	}
}

void GameSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));
}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	// 여기서 패킷 핸들러를 호출해 주어야 합니다.
}

void GameSession::OnSend(int32 len)
{
}