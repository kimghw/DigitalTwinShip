#pragma once
#include "MessageSubject.h"
#include "pch.h"
#include "EDT0001.pb.h"

class MessageSubjectManager
{

	// Singleton
public:
	static MessageSubjectManager& GetInstance()
	{
		return instance;
	}
	// Not allow to copy
	MessageSubjectManager(const MessageSubjectManager&) = delete;
	MessageSubjectManager& operator=(const MessageSubjectManager&) = delete;

private:
	MessageSubjectManager();
	static MessageSubjectManager instance;

public:

	// Set the data
	template<typename T>
	void SetMessageUpdate(T& message, int16 indexSubjects)
	{
		auto it = _pMessageSubjects.find(indexSubjects);
		if (it != _pMessageSubjects.end()) {

			// If the message subject with the given index exists, update the data
			if (it->second->GetProtocolId() == indexSubjects)
			{
				SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(message);
				it->second->Set_ReceivedData(sendBuffer);
			}
			else {
				//cout << "Type and index are not different" << endl;
			}
		}
		else {
			// Handling the case where the message subject with the given index does not exist
			// For example: output an error log, throw an exception, etc.
		}
	}

private:
	// SubscribeEvent
	template<typename T>
	void SubscribeEvent(MessageSubject<T> message, DataSessionRef* subscriber)
	{
		// here, sessionref could be called instread of input the sesionref
		int16 id = static_cast<int16>(message._protocolId);
		auto it = _pMessageSubjects.find(id);
		if (it != _pMessageSubjects.end()) {
			// If the message subject with the given ID exists, proceed with the subscription
			it->second->SubscribeEvent(subscriber);
		}
		else {
			// Handling the case where the message subject with the given ID does not exist
			// For example: output an error log, throw an exception, etc.
		}
	}
	// UnsubscribedEvent
	template<typename T>
	void UnsubscribeEvent(MessageSubject<T> message, DataSessionRef* subscriber)
	{
		int16 id = static_cast<int16>(message._protocolId);
		auto it = _pMessageSubjects.find(id);
		if (it != _pMessageSubjects.end()) {
			// If the message subject with the given ID exists, proceed with the subscription
			it->second->UnsubscribeEvent(subscriber);
		}
		else {
			// Handling the case where the message subject with the given ID does not exist
			// For example: output an error log, throw an exception, etc.
		}
	}
	
	// calls by clients
public:
	// SubscribeEvent
	void SubscribeEvent(int16 protocolId, DataSessionRef subscriber);
	// UnsubscribedEvent
	void UnsubscribeEvent(int16 protocolId, DataSessionRef subscriber);
	// SubscrbedEvnets
	void SubscribeEvents(vector<int> registered, DataSessionRef subscriber);
	// UnSubscrbedEvnets
	void UnsubscribeEvents(vector<int> registered, DataSessionRef subscriber);


public:
	USE_LOCK
	std::unordered_map<int, IMessageSubjectRef> _pMessageSubjects;
	
};
