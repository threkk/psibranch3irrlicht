#include "TempEffect.h"
#include "ParticleManager.h"
#include "ParticleModel.h"

TempEffect::TempEffect(scene::IParticleSystemSceneNode* particleNode, u32 startTime, u32 stopEmitting, u32 removeParticleAfter)
{
	this->node = particleNode;
	this->startTime = startTime;
	this->stopEmitting = stopEmitting;
	this->removeParticleAfter = removeParticleAfter;
}

bool TempEffect::isOver(u32 currentTime)
{
	std::cout << "Currenttime: " << currentTime << " stopEmitting: " << (startTime + stopEmitting) << std::endl;
	if (currentTime > startTime + stopEmitting && stopEmitting != 0)
	{
		if ( node != nullptr) {
			node->setEmitter(0);
			std::cout << "Disable emitter" << std::endl;
		} else {
			std::cout << "Node is nullptr" << std::endl;
		}
	}

	std::cout << "Currenttime: " << currentTime << " removeParticleAfter: " << (startTime + removeParticleAfter) << std::endl;
	if (currentTime > startTime + removeParticleAfter && removeParticleAfter != 0)
	{
		if ( node != nullptr)
			node->remove();
		node = nullptr;
		return true;
	}
	return false;
}

TempEffect::~TempEffect(void)
{
}

