#include "ISwitcher.h"

//! SwitchTrigger
//! Applys the observer pattern.
SwitchTrigger::SwitchTrigger(scene::ISceneNode* referenceNode)
{
	this->node = referenceNode;
	triggeringDistance = 1000;
}

//! Destructor.
SwitchTrigger::~SwitchTrigger()
{
	if(this->node) delete this->node;
	this->switchers.clear();
}

//! Attach function.
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
            //! Due to the nature of the switcher, as you want to change the things
            //! just one time, it is desactivated after being fired.
			this->switchers[i]->active = false;
			this->switchers[i]->update();
		}
	}
}

//! Checks if the nodes are close one to the other.
bool SwitchTrigger::isClose(scene::ISceneNode* other)
{
	f32 distance = node->getPosition().getDistanceFrom(other->getPosition());
	distance = abs(distance);
	if(distance <= triggeringDistance)
	{
		this->notify();
		return true;
	}else
	{
		return false;
	}
}

//! Checks if the node is close to the position.
bool SwitchTrigger::isClose(core::vector3df position)
{
	f32 distance = node->getPosition().getDistanceFrom(position);
	distance = abs(distance);
	if(distance <= triggeringDistance)
	{
		this->notify();
		return true;
	}else
	{
		return false;
	}
}

//! Switcher
Switcher::Switcher(SwitchTrigger* trg)
{
	this->active = true;
	this->trigger = trg;
    //! It adds itself during the creation of the object.
	this->trigger->attach(this);
}

Switcher::~Switcher()
{
	//TODO Delete element from the vector
	delete trigger;
}

//! Texture Switcher
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

void TextureSwitcher::setTexture(u32 textureLayer, ITexture* texture)
{
	IQualityTexture* wrapper = new IQualityTexture(texture);
	this->texture = wrapper;
	this->textureLayer = textureLayer;
}

void TextureSwitcher::update()
{
	//if(this->texture != NULL && this->textureLayer != NULL) 
	//{
		this->node->setMaterialTexture(textureLayer,texture);

	//}
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
