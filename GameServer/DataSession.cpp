#include "pch.h"
#include "DataSession.h"
#include "DataSessionManager.h"
#include "ClientPacketHandler.h"



void DataSession::OnConnected()
{
	GSessionManager.Add(static_pointer_cast<DataSession>(shared_from_this()));
	cout << "Client is connected" << endl;

	MRSchema::C_Position msg;
	msg.set_id("Hello");
	int len = msg.ByteSizeLong();
	std::vector<unsigned char> bytes(len);
	msg.SerializeToArray(bytes.data(), len);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(msg);
	this->Send(sendBuffer);

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

void DataSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<DataSession>(shared_from_this()));
}

void DataSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	
	PacketHeader* packetHeader = reinterpret_cast<PacketHeader*>(buffer);
	cout << " data is comming :"<< packetHeader->id << endl;
	cout << " The number of datas :" << len << endl;
	//std::string str(buffer, buffer + len);
	//cout << str << endl;



	PacketSessionRef session = GetPacketSessionRef();
	//Memory Usage
	cout << "Memory Usage :" << session->GetMemoryUsage() << "%" << endl;

	GPacketHandler[packetHeader->id](session, buffer, len);
	ClientPacketHandler::HandleBuffer(session, buffer, len);

}

void DataSession::OnSend(int32 len)
{

}

void DataSession::MessageUpdate(const SendBufferRef& messageFromSubject)
{
	this->Send(messageFromSubject);
}

//void DataSession::OnReceivedData(const google::protobuf::Message& proto_buf)
//{
//
//	/*int len = proto_buf.ByteSizeLong();
//	std::vector<unsigned char> bytes(len);
//	msg.SerializeToArray(bytes.data(), len);
//
//	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(msg);
//	this->Send(sendBuffer);*/
//}
