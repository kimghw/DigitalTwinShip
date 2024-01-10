#include "pch.h"
#include "MessageSubjectManager.h"

MessageSubjectManager MessageSubjectManager::instance;

MessageSubjectManager::MessageSubjectManager()
{
	MessageSubjectManager::_pMessageSubjects[EDT::Battery] = std::make_shared<MessageSubject<EDT0001::Battery>>(static_cast<int16>(EDT::Battery));
	MessageSubjectManager::_pMessageSubjects[EDT::AIS] = std::make_shared<MessageSubject<EDT0001::AIS>>(static_cast<int16>(EDT::AIS));
}

// calls by clients

	// SubscribeEvent
void MessageSubjectManager::SubscribeEvent(int16 protocolId, DataSessionRef subscriber)
{
	auto it = MessageSubjectManager::_pMessageSubjects.find(protocolId);
	if (it != MessageSubjectManager::_pMessageSubjects.end() && it->second != nullptr) {
		it->second->SubscribeEvent(subscriber);
	}
	else {
		// protocolId? ???? ??? ??? ?? ??? ?? ??
	}
}
// UnsubscribedEvent
void MessageSubjectManager::UnsubscribeEvent(int16 protocolId, DataSessionRef subscriber)
{
	auto it = MessageSubjectManager::_pMessageSubjects.find(protocolId);
	if (it != MessageSubjectManager::_pMessageSubjects.end() && it->second != nullptr) {
		it->second->UnsubscribeEvent(subscriber);
	}
	else {
		// protocolId? ???? ??? ??? ?? ??? ?? ??
	}
}
// SubscrbedEvnets
void MessageSubjectManager::SubscribeEvents(vector<int> registered, DataSessionRef subscriber)
{
	// TODO : Session should have the list
	for (const auto& num : registered)
	{
		auto it = MessageSubjectManager::_pMessageSubjects.find(num);
		if (it != MessageSubjectManager::_pMessageSubjects.end() && it->second != nullptr) {
			it->second->SubscribeEvent(subscriber);
		}
		else {
			cout << "some of the keys are not registered" << endl;
		}
	}

}
// UnSubscrbedEvnets
void MessageSubjectManager::UnsubscribeEvents(vector<int> registered, DataSessionRef subscriber)
{
	// TODO : Session should leave the list
	for (const auto& num : registered)
	{
		auto it = MessageSubjectManager::_pMessageSubjects.find(num);
		if (it != MessageSubjectManager::_pMessageSubjects.end() && it->second != nullptr) {
			it->second->UnsubscribeEvent(subscriber);
		}
		else {
			cout << "some of the keys are not registered" << endl;
		}
	}
}