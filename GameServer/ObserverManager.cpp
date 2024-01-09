#include "ObserverManager.h"

DataHandlerFunc getCastInterface[UINT16_MAX];

MessageManager::MessageManager()
{
}

MessageManager::~MessageManager()
{
}

// Add all EventPublisher into the manager
void MessageManager::Init()
{
	//ISubject* _event_battery = new EventPublisher<EDT0001::Battery>(EDT::Battery);
	//DataEventManager::_peventPublishers[EDT::Battery] = _event_battery;

	MessageManager::_pEventPublishers[EDT::Battery] = new MessagePublisher<EDT0001::Battery>(EDT::Battery);
	MessageManager::_pEventPublishers[EDT::C_Position] = new MessagePublisher<EDT0001::Battery>(EDT::C_Position);
}

// Add an EventPublisher with T into the manager
template <typename T>
void MessageManager::AddEventPublisher(int indexEnum, T* protoBuf)
{
	MessageManager::_pEventPublishers[indexEnum] = new MessagePublisher<T>(indexEnum);
}

// Delete the EventPublisher at the specified index both from the manager and heap memory
void MessageManager::DeleteEventPublisher(int indexEnum)
{
	delete MessageManager::_pEventPublishers[indexEnum];
	MessageManager::_pEventPublishers.erase(indexEnum);
}


// Add a subscriber to EventPublisher of type T at the given indexEnum in the manager
template <int indexEnum ,typename T>
void MessageManager::AddSubscriber(DataSessionRef* subscriber)
{
	//ISubject* subject = DataEventManager::_pEventPublishers[22];
	MessagePublisher<T>* dataEvent = static_cast<MessagePublisher<T>*>(MessageManager::_pEventPublishers[indexEnum]);
	dataEvent.SubscribeEvent(subscriber);

	// Enrolled data to session...
	MessageManager::_dataGroups[subscriber].push_back(indexEnum);
	MessageManager::_dataGroups1[subscriber].push_back(dataEvent);
}

// Delete the subscriber to EventPublisher of type T at the given indexEnum in the manager
template <int indexEnum, typename T>
void MessageManager::DeleteSubscriber(DataSessionRef* subscriber)
{
	//ISubject* subject = DataEventManager::_pEventPublishers[22];
	MessagePublisher<T> dataEvent = static_cast<MessagePublisher<T>>(MessageManager::_pEventPublishers[indexEnum]);
	dataEvent.UnsubscribeEvent(subscriber);
}

void MessageManager::Broadcast()
{
	for ( const auto& element : MessageManager::_dataGroups)
	{
		DataSessionRef session = element.first;
		const vector<int16>& dataGroup = element.second;
		SendBufferRef sendBuffer;
		for ( const auto& index : dataGroup)
		{
			auto data = MessageManager::GetReceivedData(index);
			sendBuffer = ClientPacketHandler::MakeSendBuffer(*data);
		}
	}
}
