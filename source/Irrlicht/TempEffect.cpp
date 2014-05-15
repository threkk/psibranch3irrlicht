#include "TempEffect.h"
#include "ParticleManager.h"
#include "ParticleModel.h"

ParticleModel model = ParticleModel();

TempEffect::TempEffect(scene::IParticleSystemSceneNode* particleNode, u32 startTime, u32 StopEmitting, u32 RemoveParticleAfter)
{

}

bool TempEffect::isOver(u32 currentTime)
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

