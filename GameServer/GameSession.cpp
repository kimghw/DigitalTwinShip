#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"



void GameSession::OnConnected()
{
	GSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "Client is connected" << endl;

	//Protocol::S_TEST pkt;
	//pkt.set_id(1);
	//pkt.set_player("G");
	//
	//auto sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt);

	//while (true)
	//{
	//	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	//	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//	std::cout << "Send size : "<< sizeof(sendBuffer) << std::endl;
	//	this->Send(sendBuffer);
	//	cout << "Send S_TEST : Successful" << endl;
	//	break;
	//}
}

void GameSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));
}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{

	PacketHeader* packetHeader = reinterpret_cast<PacketHeader*>(buffer);
	cout << " data is comming :"<< packetHeader->id << endl;
	cout << " The number of datas :" << len << endl;
	std::string str(buffer, buffer + len);
	//cout << str << endl;

	PacketSessionRef session = GetPacketSessionRef();
	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void GameSession::OnSend(int32 len)
{

}