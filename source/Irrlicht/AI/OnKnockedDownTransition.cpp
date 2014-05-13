#include "ai\OnKnockedDownTransition.h"


OnKnockedDownTransition::OnKnockedDownTransition(int* hp) : health(hp), Transition()
{
}

OnKnockedDownTransition::OnKnockedDownTransition(int* hp, State* target) : health(hp), Transition(target)
{
}


OnKnockedDownTransition::~OnKnockedDownTransition()
{

}

bool OnKnockedDownTransition::condition()
{
	if ( health == NULL ) return false;
	return *health <= 0;
}

void OnKnockedDownTransition::setHealth(int* health)
{
	this->health = health;
}