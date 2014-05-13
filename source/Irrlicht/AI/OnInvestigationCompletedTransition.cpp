#include "ai\OnInvestigationCompletedTransition.h"

OnInvestigationCompletedTransition::OnInvestigationCompletedTransition
	(Detectable *owner, float attentionSpan, float visionLength, std::string topic)
	: owner(owner), attentionSpan(attentionSpan), visionLength(visionLength), topic(topic), Transition()
{
	generateId();
	subscribe(topic);
	reset();
}

OnInvestigationCompletedTransition::OnInvestigationCompletedTransition
	(Detectable *owner, float attentionSpan, float visionLength, std::string topic, State* state)
	: owner(owner), attentionSpan(attentionSpan), visionLength(visionLength), topic(topic), Transition(state)
{
	generateId();
	subscribe(topic);
	reset();
}

OnInvestigationCompletedTransition::~OnInvestigationCompletedTransition()
{
	cancelSubscription(topic);
}

bool OnInvestigationCompletedTransition::condition()
{
	// Update timer
	now = device->getTimer()->getTime();
	frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;

	// If NPC can see the point
	if (owner->getPosition().getDistanceFrom(point) <= visionLength)
	{
		// Increase the timer
		timer += frameDeltaTime;

		// If the timer is larger than the amount of time the NPC wants to look at the point
		if (timer >= attentionSpan)
		{
			return true;
		}
	}
	return false;
}

void OnInvestigationCompletedTransition::reset()
{
	// Reset timer variables
	now = then = device->getTimer()->getTime();
	timer = 0;
}

void OnInvestigationCompletedTransition::receiveMessage(MessageObject object)
{
	point = *(irr::core::vector3df*)object.vMessage;
}