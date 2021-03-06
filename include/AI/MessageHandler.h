#pragma once

#include <vector>
#include <map>
#include "ai\MessageClient.h"

/**
 * MessageHandler
 * Clients can subscribe topics from the message client
 * All messages send to an topic will be delivered to all registered clients
 */
class __declspec(dllexport) MessageHandler
{
public:
	
	virtual ~MessageHandler(void);

	/**
	 * Subscribes a topic for the client
	 */
	void addListener(std::string topic, MessageClient* client);

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
	 * Returns the number of all clients
	 */
	unsigned int getNumberOfClients();

	/**
	 * Returns the number of all topics
	 */
	unsigned int getNumberOfTopics();

	/**
	 * Returns the number of clients that are registered for a topic
	 */
	unsigned int getNumberOfClients(std::string topic);

	/**
	 * Returns the number of topics that a client has subscribed
	 */
	unsigned int getNumberOfTopics(MessageClient* client);

	/**
	 * Returns the number of topics that a client has subscribed
	 */
	unsigned int getNumberOfTopics(int id);

	/**
	 * Removes all clients
	 */
	void clear();

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
	 * This struct is used for the map and contains the client and it's topics
	 */
	struct clientTopic
	{
		MessageClient* client;
		std::vector<std::string> subscribedTopics;

		clientTopic(){}

		clientTopic(MessageClient* client, std::vector<std::string> topics) 
			: client(client), subscribedTopics(topics) {}
	};

	/**
	 * Contains all clients by their ID and Topics
	 * Key: ID
	 * Value: ClientPointer
	 */
	std::map<int, clientTopic> clients;

	/**
	 * Contains the clients for the topics
	 * Key: Topic
	 * Value: List with clients
	 */
	std::map<std::string, std::vector<MessageClient*>> topicClients;
	
};

