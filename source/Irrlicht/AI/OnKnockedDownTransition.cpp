#include "AI\OnKnockedDownTransition.h"


OnKnockedDownTransition::OnKnockedDownTransition(unsigned int* hp)
{
	health = hp;
}


OnKnockedDownTransition::~OnKnockedDownTransition()
{

}

bool OnKnockedDownTransition::condition()
{
	return &health <= 0;
}