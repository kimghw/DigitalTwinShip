#pragma once
#include "MessageEvent.h"
#include "pch.h"
#include <google/protobuf/message.h>

using DataHandlerFunc = std::function<SendBufferRef(IMessagePublisher&)>;
extern DataHandlerFunc GDataHandler[UINT16_MAX];



class MessageManager
{
//singleton

	//TODO: EvnetPublisher initialization

public:

	MessageManager();
	~MessageManager();

	static void Init()
	{

		//TODO : ??? ?? ?? ???.
		GDataHandler[EDT::Battery] = [](IMessagePublisher& iSubject) -> SendBufferRef
		{return ClientPacketHandler::MakeSendBuffer(static_cast<MessagePublisher<EDT0001::Battery>&>(iSubject)._proto);};
			
	}

	template <typename T>
	T* GetReceivedData(int index); // ?? ??? ?? ??
	template <>
	EDT0001::Battery* GetReceivedData<EDT0001::Battery>(int index) {
		return static_cast<MessagePublisher<EDT0001::Battery>*>(_pEventPublishers[index])->_proto;
	}


private:
	template <typename T>
	void AddEventPublisher(int indexEnum, T* protoBuf);
	void DeleteEventPublisher(int indexEnum);

public:
	//GDataEventhandler[EDT::Battery] = [](){return MakeSendBuffer(pkt)}

public:
	template <int indexEnum, typename T>
	void AddSubscriber(DataSessionRef* subscriver);
	template <int indexEnum, typename T>
	void DeleteSubscriber(DataSessionRef* subscriver);

	void Broadcast();

	//

	EDT0001::Battery* GetReceivedData<EDT::Battery>() { return static_cast<MessagePublisher<EDT0001::Battery>*>(_pEventPublishers[index])->_proto; }
	EDT0001::Battery1* GetReceivedData<EDT::Battery1>() { return static_cast<EventPublisher<EDT0001::Battery1>*>(_pEventPublishers[index])->_proto; }
	

public:
	USE_LOCK;
	std::map<int, IMessagePublisher*> _pEventPublishers;
	USE_LOCK;
	set<DataSessionRef> _sessions;
	USE_LOCK;
	std::map<DataSessionRef, vector<int16>>	    _dataGroups;
	std::map<DataSessionRef, vector<IMessagePublisher*>> _dataGroups1;
};



extern MessageManager GDataEventManager;