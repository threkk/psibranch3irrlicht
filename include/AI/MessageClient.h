#pragma once

#include <string>
#include "ai\MessageObject.h"

/**
 * MessageClient
 * A Message client can register to the Message System to receive and send new messages.
 * A client is able to subscribe topics to receive all messages will be send to that topic.
 *
 * To use the message system inherit this abstract class.
 * Every class that is a subclass of MessageClient will be able to communicate with other classes.
 */
class __declspec(dllexport) MessageClient
{

public:

	virtual ~MessageClient(void)
	{
	}

	/**
	 * This method will be called when a new message is received
	 */
	virtual void receiveMessage(MessageObject message) = 0;

	/**
	 * Returns the ID of the message client
	 */
	int getID();

protected:

	/**
	 * Will generate an unique Identifier
	 * The generated ID will also be saved in the member variable ID
	 *
	 * This method must be called before registering to the message system to ensure
	 * that the object has an unique id
	 */
	int generateId();

	/**
	 * Subscribe a topic
	 * The object will receive messages that are send to this topic
	 */
	void subscribe(std::string topic);

	/**
	 * Deregisters the object from the subscription
	 * The object will no longer get messages from this topic
	 */
	void cancelSubscription(std::string topic);

	/**
	 * Sends a new message to all other objects
	 */
	void sendMessageToAll(MessageObject message);

	/**
	 * Sends a new message to an other object
	 */
	void sendMessageToObject(MessageObject message, int id);

	/**
	 * Sends a new message to an other object
	 */
	void MessageClient::sendMessageToObject(MessageObject message, MessageClient *client);

	/**
	 * Sends a new message to all receivers that subscibed the given topic
	 */
	void sendMessageToTopic(MessageObject message, std::string topic);

private:
	static int count;
	int message_id;
};