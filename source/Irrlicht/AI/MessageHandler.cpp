#include "AI\MessageHandler.h"
#include <algorithm>

MessageHandler* MessageHandler::instance = NULL;

MessageHandler::MessageHandler(void)
{
}

MessageHandler::MessageHandler(MessageHandler& object)
{
}

MessageHandler::~MessageHandler(void) 
{
}

void MessageHandler::addListener(std::string topic, MessageClient* client)
{
	// Check if the topic is existing
	if ( topicClients.find(topic) == topicClients.end() ) 
	{
		// Not existing -> Create new list
		topicClients[topic] = std::vector<MessageClient*>();
	}

	// Check if list contains the client
	if ( std::find(topicClients[topic].begin(), topicClients[topic].end(), client) == topicClients[topic].end()) 
	{
		// Client is not contained
		topicClients[topic].push_back(client);
	}

	// Check if client is already in the list
	if ( clients.find(client->getID()) == clients.end() ) 
	{
		// Client doesn't exist -> Add it
		clients[client->getID()] = clientTopic(client, std::vector<std::string>());
	}

	// Check if client already contains topic
	if ( std::find(clients[client->getID()].subscribedTopics.begin(), 
		clients[client->getID()].subscribedTopics.end(), topic) == clients[client->getID()].subscribedTopics.end()) 
	{
		// Topic is not contained
		clients[client->getID()].subscribedTopics.push_back(topic);
	}
}

void MessageHandler::removeListener(std::string topic, MessageClient* client)
{
	// Check if the topic is existing
	if ( topicClients.find(topic) != topicClients.end() ) 
	{
		// Topic Existing
		// Remove client from the topic list
		topicClients[topic].erase(
			std::remove(topicClients[topic].begin(),
			topicClients[topic].end(), client),
			topicClients[topic].end());

		// No more clients?
		if ( topicClients[topic].empty() )
		{
			// Remove client
			topicClients.erase(topic);
		}
	}

	// Check if client is registered
	if ( clients.find(client->getID()) != clients.end() ) 
	{
		// Client existing
		// Remove topic from client
		clients[client->getID()].subscribedTopics.erase(
			std::remove(clients[client->getID()].subscribedTopics.begin(),
			clients[client->getID()].subscribedTopics.end(), topic),
			clients[client->getID()].subscribedTopics.end());

		// No more topics?
		if ( clients[client->getID()].subscribedTopics.empty() )
		{
			// Remove client
			clients.erase(client->getID());
		}
	}
}

void MessageHandler::notifyListeners(MessageObject message)
{
	for (std::map<int, clientTopic>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		// First value of iterator is key, second is the client
		it->second.client->receiveMessage(message);
	}
}

void MessageHandler::notifyListenersTopic(MessageObject message, std::string topic)
{
	if ( topicClients.find(topic) != topicClients.end() ) {
		// Topic exists
		
		// Set topic to message
		message.topic = topic;

		// Send messages
		// Copy list, because the origin will be changed
		std::vector<MessageClient*> list = std::vector<MessageClient*>(topicClients[topic]);
		for ( std::vector<MessageClient*>::iterator it = list.begin(); it != list.end(); ++it)
		{
			(*it)->receiveMessage(message);
		}
	}
}

bool MessageHandler::notifyListener(MessageObject message, int id)
{
	if (clients.find(id) != clients.end() ) {
		// Client exists
		clients[id].client->receiveMessage(message);
		return true;
	}
	return false;
}

unsigned int MessageHandler::getNumberOfClients()
{
	return clients.size();
}

unsigned int MessageHandler::getNumberOfTopics()
{
	return topicClients.size();
} 

unsigned int MessageHandler::getNumberOfClients(std::string topic)
{
	if (topicClients.find(topic) != topicClients.end() ) {
		// Topic exists
		return topicClients[topic].size();
	}
	return 0;
}

unsigned int MessageHandler::getNumberOfTopics(MessageClient* client)
{
	return getNumberOfTopics(client->getID());
}

unsigned int MessageHandler::getNumberOfTopics(int id)
{
	if (clients.find(id) != clients.end() ) {
		// Client exists
		return clients[id].subscribedTopics.size();
	}
	return 0;
}

void MessageHandler::clear()
{
	clients.clear();
	topicClients.clear();
}

MessageHandler* MessageHandler::getInstance()
{
	if ( instance == NULL ) instance = new MessageHandler();
	return instance;
}

