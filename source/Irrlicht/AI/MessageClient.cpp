#include "ai\MessageClient.h"
#include "ai\MessageHandler.h"

int MessageClient::count = 0;

int MessageClient::generateId()
{
	message_id = count++;
	return message_id;
}

void MessageClient::subscribe(std::string topic)
{
	MessageHandler::getInstance()->addListener(topic, this);
}

void MessageClient::cancelSubscription(std::string topic)
{
	MessageHandler::getInstance()->removeListener(topic, this);
}

void MessageClient::sendMessageToAll(MessageObject message)
{
	MessageHandler::getInstance()->notifyListeners(message);
}

void MessageClient::sendMessageToObject(MessageObject message, int id)
{
	MessageHandler::getInstance()->notifyListener(message, id);
}

void MessageClient::sendMessageToObject(MessageObject message, MessageClient *client)
{
	MessageHandler::getInstance()->notifyListener(message, client->getID());
}

void MessageClient::sendMessageToTopic(MessageObject message, std::string topic)
{
	MessageHandler::getInstance()->notifyListenersTopic(message, topic);
}

int MessageClient::getID()
{
	return message_id;
}