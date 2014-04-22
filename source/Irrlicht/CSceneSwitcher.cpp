#include "ISceneSwitcher.h"

ISceneSwitcher::ISceneSwitcher(ISceneManager* smgr)
{
	this->smgr = smgr;
	this->switches = new std::vector<SScene>();
}

ISceneSwitcher::~ISceneSwitcher()
{
	for(unsigned i = 0; i < this->switches->size(); i++)
	{
		this->switches->at(i).nextScene->smngr->drop();
	}

	this->switches->clear();

	if(this->switches) delete this->switches;
}

bool ISceneSwitcher::dropSwitch(int index)
{

}

int addSwitch(NScene* nextScene, 
			core::vector3df switchPosition, 
			core::vector3df newPosition);


void update();

