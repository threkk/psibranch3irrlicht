#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "ISceneManager.h"
#include "MessageClient.h"
#include <functional>

/**
 * Checks if there was a message for the topic
 */
class __declspec(dllexport) OnMessageTransition: public Transition, public MessageClient
{
public:
	OnMessageTransition(std::string topic);
	OnMessageTransition(std::string topic, State* state);
	OnMessageTransition(std::string topic, std::function<void(MessageObject message)> onMessageCallback, State* state);
	~OnMessageTransition();

	virtual bool condition();
	virtual void reset();

	virtual void receiveMessage(MessageObject message);

	std::function<void(MessageObject message)> onMessageCallback;

protected:
	std::string topic;
	bool messageReceived;
	bool subscribed;
};

