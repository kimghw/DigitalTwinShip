#pragma once
#include "pch.h"
#include <vector>
#include <algorithm>
#include "DataSession.h"

class IMessageSubject {
public:
    IMessageSubject(int16_t protocolId) : _protocolId(protocolId) {}
    virtual ~IMessageSubject() = default;
    virtual void SubscribeEvent(DataSessionRef subscriber) = 0;
    virtual void UnsubscribeEvent(DataSessionRef subscriber) = 0;
    virtual int16 GetProtocolId() = 0;
    virtual void Set_ReceivedData(SendBufferRef sendBuffer) = 0;
protected:
    const int16_t _protocolId;
};

template <typename T>
class MessageSubject : public IMessageSubject 
{
public:
    MessageSubject(int16 protocolId) : IMessageSubject(protocolId) {}
    int16 GetProtocolId() { return _protocolId; }

    void SubscribeEvent(DataSessionRef subscriber) override 
    {
        _subscribers.push_back(subscriber);
    }

    void UnsubscribeEvent(DataSessionRef subscriber) override 
    {
        auto it = std::find(_subscribers.begin(), _subscribers.end(), subscriber);
        if (it != _subscribers.end()) {
            _subscribers.erase(it);
        }
        else {
            throw std::runtime_error{ "Subscriber not found" };
            //std::cout << "Subscriber not found, no action taken." << std::endl;
        }
    }

	//void Set_ReceivedData(T&& proto_buf)
	//{
	//	_proto = std::move(proto_buf);
	//	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(_proto);
	//	NotifyToSubscribers(sendBuffer);
	//}

	void Set_ReceivedData(SendBufferRef sendBuffer)
	{
		NotifyToSubscribers(sendBuffer);
	}

private: 
    void NotifyToSubscribers(SendBufferRef buffer) 
    {
        USE_LOCK;
        for (DataSessionRef subscriber : _subscribers)
        {
            subscriber->MessageUpdate(buffer);
        }
    }
public:
    //T* _proto;
    std::vector<DataSessionRef> _subscribers;
};
