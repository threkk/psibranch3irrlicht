#include "AI\MessageHandler.h"
#include <algorithm>

MessageHandler::MessageHandler(void)
{
}

MessageHandler::MessageHandler(MessageHandler& object)
{
}

MessageHandler::~MessageHandler(void) 
{
}

void MessageHandler::addListener(MessageClient* object)
{
	clients[object->getID()] = object;
}

void MessageHandler::addListener(std::string topic, MessageClient* client)
{
	topicClients[topic].push_back(client);
}

void MessageHandler::removeListener(int id)
{
	clients.erase(id);
}

void MessageHandler::removeListener(MessageClient* client)
{
	clients.erase(client->getID());
}

void MessageHandler::removeListener(std::string topic, MessageClient* client)
{
	// Remove client from the topic list
	topicClients[topic].erase(
		std::remove(topicClients[topic].begin(),
		topicClients[topic].end(), client),
		topicClients[topic].end());
}

void MessageHandler::notifyListeners(MessageObject message)
{
	for (std::map<int, MessageClient*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		// First value of iterator is key, second is the client
		it->second->receiveMessage(message);
	}
}

void MessageHandler::notifyListenersTopic(MessageObject message, std::string topic)
{
	if ( topicClients.find(topic) != topicClients.end() ) {
		// Topic exists
		
		for ( std::vector<MessageClient*>::iterator it = topicClients[topic].begin(); it != topicClients[topic].end(); ++it)
		{
			(*it)->receiveMessage(message);
		}
	}
}

bool MessageHandler::notifyListener(MessageObject message, int id)
{
	if (clients.find(id) != clients.end() ) {
		// Topic exists
		clients[id]->receiveMessage(message);
		return true;
	}
	return false;
}

MessageHandler* MessageHandler::getInstance()
{
	if ( instance == NULL ) instance = new MessageHandler();
	return instance;
}

