#pragma once
#include "Session.h"
//#include "MessageEvent.h"
#include "MessageObserver.h"

class DataSession : public PacketSession, public IMessageObserver
{
public:
	~DataSession()
	{
		cout << "~DataSession" << endl;
	}

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;

	//virtual void MessageUpdate(const SendBufferRef messageFromSubject) override;

	//void OnReceivedData(const google::protobuf::Message& proto_buf);
};