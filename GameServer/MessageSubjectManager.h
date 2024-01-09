#pragma once
#include "MessageSubject.h"
#include "pch.h"
#include "EDT0001.pb.h"

class MessageSubjectManager
{
public:
	static MessageSubjectManager& GetInstance()
	{
		return instance;
	}

	MessageSubjectManager(const MessageSubjectManager&) = delete;
	MessageSubjectManager& operator=(const MessageSubjectManager&) = delete;

private:
	MessageSubjectManager(){}
	static MessageSubjectManager instance;

public:

	void Init()
	{
		_pMessageSubjects[EDT::Battery] = std::make_shared<MessageSubject<EDT0001::Battery>>(static_cast<int16>(EDT::Battery));
		_pMessageSubjects[EDT::AIS] = std::make_shared<MessageSubject<EDT0001::AIS>>(static_cast<int16>(EDT::AIS));
	}

	// Set the data
	template<typename T>
	void SetMessageUpdate(T& dataType, int16 indexSubjects)
	{
		auto it = _pMessageSubjects.find(indexSubjects);
		if (it != _pMessageSubjects.end()) {

			// If the message subject with the given index exists, update the data
			if (it->second->GetProtocolID() == indexSubjects)
			{
				 it->second->Set_ReceivedData(dataType);
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
	void SubscribeEvent(int16 protocolId, DataSessionRef* subscriber) 
	{
		auto it = _pMessageSubjects.find(protocolId);
		if (it != _pMessageSubjects.end() && it->second != nullptr) {
			it->second->SubscribeEvent(subscriber);
		}
		else {
			// protocolId? ???? ??? ??? ?? ??? ?? ??
		}
	}
	// UnsubscribedEvent
	void UnsubscribeEvent(int16 protocolId, DataSessionRef* subscriber)
	{
		auto it = _pMessageSubjects.find(protocolId);
		if (it != _pMessageSubjects.end() && it->second != nullptr) {
			it->second->UnsubscribeEvent(subscriber);
		}
		else {
			// protocolId? ???? ??? ??? ?? ??? ?? ??
		}
	}
	// SubscrbedEvnets
	void SubscribeEvents(vector<int> registered, DataSessionRef* subscriber)
	{
		// TODO : Session should have the list
		for (const auto& num : registered)
		{
			auto it = _pMessageSubjects.find(num);
			if (it != _pMessageSubjects.end() && it->second != nullptr) {
				it->second->SubscribeEvent(subscriber);
			}
			else {
				cout << "some of the keys are not registered" << endl;
			}
		}

	}
	// UnSubscrbedEvnets
	void UnsubscribeEvents(vector<int> registered, DataSessionRef* subscriber)
	{
		// TODO : Session should leave the list
		for (const auto& num : registered)
		{
			auto it = _pMessageSubjects.find(num);
			if (it != _pMessageSubjects.end() && it->second != nullptr) {
				it->second->UnsubscribeEvent(subscriber);
			}
			else {
				cout << "some of the keys are not registered" << endl;
			}
		}
	}

public:
	std::map<int, IMessageSubjectRef> _pMessageSubjects;
	
};
