#include "ai\OnMessageTransition.h"

OnMessageTransition::OnMessageTransition(std::string topic)
	: topic(topic), onMessageCallback(NULL), Transition()
{
	generateId();
	reset();
}

OnMessageTransition::OnMessageTransition(std::string topic, State* state)
	: topic(topic), onMessageCallback(NULL), Transition(state)
{
	generateId();
	reset();
}

OnMessageTransition::OnMessageTransition(std::string topic, std::function<void(MessageObject message)> onMessageCallback, State* state)
	: topic(topic), onMessageCallback(onMessageCallback), Transition(state)
{
	generateId();
	reset();
}

OnMessageTransition::~OnMessageTransition()
{
}

bool OnMessageTransition::condition()
{
	if ( !subscribed )
	{
		subscribe(topic);
		subscribed = true;
	}
	return messageReceived;
}

void OnMessageTransition::reset()
{
	cancelSubscription(topic);
	messageReceived = false;
	subscribed = false;
}

void OnMessageTransition::receiveMessage(MessageObject message)
{
	// Set flag to true
	messageReceived = true;

	// Call onMessageCallback
	if ( onMessageCallback != NULL ) 
	{
		onMessageCallback(message);
	}
}