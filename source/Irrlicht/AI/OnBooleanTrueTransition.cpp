#include "ai\OnBooleanTrueTransition.h"

OnBooleanTrueTransition::OnBooleanTrueTransition(bool *boolean)
	: boolean(boolean), Transition()
{
}

OnBooleanTrueTransition::OnBooleanTrueTransition(bool *boolean, State* state)
	: boolean(boolean), Transition(state)
{
}

OnBooleanTrueTransition::~OnBooleanTrueTransition()
{
}

bool OnBooleanTrueTransition::condition()
{
	return *boolean;
}