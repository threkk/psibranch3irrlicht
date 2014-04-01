#pragma once

#include <vector>
#include <map>
#include "ai\MessageClient.h"

class __declspec(dllexport) MessageHandler
{
public:
	
	virtual ~MessageHandler(void);

	/**
	 * Register a new client
	 */
	void addListener(MessageClient* object);

	/**
	 * Subscribes a topic for the client
	 */
	void addListener(std::string topic, MessageClient* client);

	/**
	 * Remove an Client with íts ID
	 */
	void removeListener(int id);

	/**
	 * Remove an Client
	 */
	void removeListener(MessageClient* client);

	/**
	 * Remove an Client from a topic
	 */
	void removeListener(std::string topic, MessageClient* client);

	/**
	 * Notify all clients with this message
	 */
	void notifyListeners(MessageObject message);

	/**
	 * Sends this message to all clients that subscribed that 
	 */
	void notifyListenersTopic(MessageObject message, std::string topic);

	/**
	 * Sends this message to the client with the given ID
	 * Returns true when the message could be send successfully
	 */
	bool notifyListener(MessageObject message, int id);

	/**
	 * Get an the instance of the MessageHandler
	 */
	static MessageHandler* getInstance();
private:

	MessageHandler(void);
	MessageHandler(MessageHandler& object);

	// Singleton instance
	static MessageHandler* instance;

	/**
	 * Contains the clients
	 * Key: ID
	 * Value: ClientPointer
	 */
	std::map<int, MessageClient*> clients;

	/**
	 * Contains the clients for the topics
	 * Key: Topic
	 * Value: List with clients
	 */
	std::map<std::string, std::vector<MessageClient*>> topicClients;
	
};

