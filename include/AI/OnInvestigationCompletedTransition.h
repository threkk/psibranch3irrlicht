#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "ISceneManager.h"
#include "MessageClient.h"

class __declspec(dllexport) OnInvestigationCompletedTransition: public Transition, public MessageClient
{
public:
	OnInvestigationCompletedTransition(Detectable *owner, float attentionSpan, float visionLength, std::string topic);
	OnInvestigationCompletedTransition(Detectable *owner, float attentionSpan, float visionLength, std::string topic, State* state);
	~OnInvestigationCompletedTransition();

	bool condition();
	void reset();

	void receiveMessage(MessageObject object);

private:
	Detectable *owner;
	irr::core::vector3df point;

	// How long state owner should look at point
	float attentionSpan;

	// From what distance state owner can see the point
	float visionLength;

	// Timer variables
	irr::u32 now;
	irr::u32 then;
	irr::f32 frameDeltaTime;
	irr::f32 timer;

	// Irrlicht device
	irr::IrrlichtDevice* device;

	std::string topic;
};

