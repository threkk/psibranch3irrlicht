#include "TempEffect.h"
#include "ParticleManager.h"
#include "ParticleModel.h"

ParticleModel model = ParticleModel();

TempEffect::TempEffect()
{

}

bool TempEffect::isOver(int currentTime)
{
	if (currentTime > startTime + model.getStopEmitting())
	{
		node->setEmitter(0);
	}

	if (currentTime > startTime + model.getRemoveParticleAfter())
	{
		return true;
	}
	return false;
}

TempEffect::~TempEffect(void)
{
}

