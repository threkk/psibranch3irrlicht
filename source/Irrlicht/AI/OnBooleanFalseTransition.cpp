#include "ai\OnBooleanFalseTransition.h"

OnBooleanFalseTransition::OnBooleanFalseTransition(bool *boolean)
	: boolean(boolean), Transition()
{
}

OnBooleanFalseTransition::OnBooleanFalseTransition(bool *boolean, State* state)
	: boolean(boolean), Transition(state)
{
}

OnBooleanFalseTransition::~OnBooleanFalseTransition()
{
}

bool OnBooleanFalseTransition::condition()
{
	return !(*boolean);
}