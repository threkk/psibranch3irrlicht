#include "ISwitcher.h"

// SwitchTrigger

SwitchTrigger::SwitchTrigger(scene::ISceneNode* referenceNode)
{
	this->node = referenceNode;
}

SwitchTrigger::~SwitchTrigger()
{
	if(this->node) delete this->node;
	this->switchers.clear();
}

void SwitchTrigger::attach(Switcher* swt)
{
	this->switchers.push_back(swt);
}

void SwitchTrigger::notify()
{
	for(int i = 0; i < this->switchers.size(); i++)
	{
		if(this->switchers[i]->active)
		{
			this->switchers[i]->active = false;
			this->switchers[i]->update();
		}
	}
}

bool SwitchTrigger::isClose(scene::ISceneNode* other)
{
	if(	((node->getPosition().X - (node->getBoundingBox().MaxEdge.X)) < (other->getPosition().X + (other->getBoundingBox().MaxEdge.X)) && (node->getPosition().X + (node->getBoundingBox().MaxEdge.X)) > (other->getPosition().X - (other->getBoundingBox().MaxEdge.X ))) &&
		((node->getPosition().Y + (node->getBoundingBox().MaxEdge.Y)) > (other->getPosition().Y - (other->getBoundingBox().MaxEdge.Y)) && (node->getPosition().Y - (node->getBoundingBox().MaxEdge.Y)) < (other->getPosition().Y + (other->getBoundingBox().MaxEdge.Y ))) &&
		((node->getPosition().Z + (node->getBoundingBox().MaxEdge.Z)) > (other->getPosition().Z - (other->getBoundingBox().MaxEdge.Z)) && (node->getPosition().Z - (node->getBoundingBox().MaxEdge.Z)) < (other->getPosition().Z + (other->getBoundingBox().MaxEdge.Z ))))
	{
		this->notify();
		return true;
	}else
	{
		return false;
	}
}

bool SwitchTrigger::isClose(core::vector3df position)
{
	if(	((node->getPosition().X - node->getBoundingBox().MaxEdge.X) < position.X) && (node->getPosition().X + node->getBoundingBox().MaxEdge.X) > position.X &&
		((node->getPosition().Y + node->getBoundingBox().MaxEdge.Y) > position.Y) && (node->getPosition().Y - node->getBoundingBox().MaxEdge.Y) < position.Y &&
		((node->getPosition().Z + node->getBoundingBox().MaxEdge.Z) > position.Z) && (node->getPosition().Z - node->getBoundingBox().MaxEdge.Z) < position.Z )
	{
		this->notify();
		return true;
	}else
	{
		return false;
	}
}

// Switcher

Switcher::Switcher(SwitchTrigger* trg)
{
	this->active = true;
	this->trigger = trg;
	this->trigger->attach(this);
}

Switcher::~Switcher()
{
	//TODO Delete element from the vector
	delete trigger;
}

// Texture Switcher
TextureSwitcher::TextureSwitcher(SwitchTrigger* trigger, scene::ISceneNode* dst) : Switcher(trigger)
{
	this->node = dst;
	this->texture = NULL;
	this->textureLayer = NULL;
}

TextureSwitcher::~TextureSwitcher()
{
	if(this->node) delete this->node;
	if(this->texture) delete this->texture;
}

void TextureSwitcher::setTexture(u32 textureLayer, IQualityTexture* texture)
{
	this->texture = texture;
	this->textureLayer = textureLayer;
}

void TextureSwitcher::update()
{
	if(this->texture != NULL && this->textureLayer != NULL) 
	{
		this->node->setMaterialTexture(textureLayer,texture);

	}
}

// Scene Switcher
SceneSwitcher::SceneSwitcher(SwitchTrigger* trigger, scene::ISceneSeamlessLoader* smgr) : Switcher(trigger)
{
	this->smgr = smgr;
	this->sceneIndex = NULL;
}

SceneSwitcher::~SceneSwitcher()
{
	// We do not want to delete the sceneManager.
	// if(this->smgr) delete smgr;
}

void SceneSwitcher::setScene(int sceneIndex)
{
	this->sceneIndex = sceneIndex;
}

void SceneSwitcher::update()
{
	if(this->sceneIndex != NULL)
	{
		this->smgr->setScene(this->sceneIndex);
	}
}