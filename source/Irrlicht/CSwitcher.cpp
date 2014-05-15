#include "ISwitcher.h"

// SwitchTrigger

SwitchTrigger::SwitchTrigger(scene::ISceneNode* node)
{
	this->node = node;
}

SwitchTrigger::~SwitchTrigger()
{
	delete node;
}

bool SwitchTrigger::isClose(scene::ISceneNode* other)
{
	if(	((node->getPosition().X - (node->getBoundingBox().MaxEdge.X)) < (other->getPosition().X + (other->getBoundingBox().MaxEdge.X)) && (node->getPosition().X + (node->getBoundingBox().MaxEdge.X)) > (other->getPosition().X - (other->getBoundingBox().MaxEdge.X ))) &&
		((node->getPosition().Y + (node->getBoundingBox().MaxEdge.Y)) > (other->getPosition().Y - (other->getBoundingBox().MaxEdge.Y)) && (node->getPosition().Y - (node->getBoundingBox().MaxEdge.Y)) < (other->getPosition().Y + (other->getBoundingBox().MaxEdge.Y ))) &&
		((node->getPosition().Z + (node->getBoundingBox().MaxEdge.Z)) > (other->getPosition().Z - (other->getBoundingBox().MaxEdge.Z)) && (node->getPosition().Z - (node->getBoundingBox().MaxEdge.Z)) < (other->getPosition().Z + (other->getBoundingBox().MaxEdge.Z ))))
	{
		return true;
	}else
	{
		return false;
	}
}

bool SwitchTrigger::isClose(core::vector3df position)
{
	if(	(node->getPosition().X - node->getBoundingBox().MaxEdge.X) < position.X) && (node->getPosition().X + node->getBoundingBox().MaxEdge.X) > position.X &&
		(node->getPosition().Y + node->getBoundingBox().MaxEdge.Y) > position.Y) && (node->getPosition().Y - node->getBoundingBox().MaxEdge.Y) < position.Y &&
		(node->getPosition().Z + node->getBoundingBox().MaxEdge.Z) > position.Z) && (node->getPosition().Z - node->getBoundingBox().MaxEdge.Z) < position.Z )
	{
		return true;
	}else
	{
		return false;
	}
}

// Switcher

Switcher::Switcher(SwitchTrigger* trg)
{
	this->trigger = trg;
}
