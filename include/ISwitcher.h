#include "ISceneNode.h"
#include "IQualityTexture.h"
#include "IAnimatedMeshSceneNode.h"
#include "ISceneSeamlessLoader.h";
#include <vector>

using namespace irr;

namespace irr {
namespace video {
	

// SwitchTrigger : Observable
class IRRLICHT_API SwitchTrigger
{
private:
	scene::ISceneNode* node;
	std::vector <class Switcher *> switchers;
public:
	SwitchTrigger(scene::ISceneNode* referenceNode);
	~SwitchTrigger();
	void attach(Switcher* swt);
	void notify();
	bool isClose(scene::ISceneNode* other);
	bool isClose(core::vector3df position);
};

// Switcher : Parent observer
class Switcher 
{
private:
	SwitchTrigger* trigger;
public:
	Switcher(SwitchTrigger* trg);
	~Switcher();
	virtual void update()=0;
};

// TextureSwitcher : Observer
class IRRLICHT_API TextureSwitcher : public Switcher
{
private:
	IQualityTexture* texture;
	u32 textureLayer;
	scene::ISceneNode* node;
public:
	TextureSwitcher(SwitchTrigger* trigger, scene::ISceneNode* dst);
	~TextureSwitcher();
	void setTexture(u32 textureLayer, IQualityTexture* texture);
	void update();
};

// MeshSwitcher : Observer
class IRRLICHT_API MeshSwitcher : public Switcher
{
private:
	ISceneNode* mesh;
public:
	MeshSwitcher(SwitchTrigger* trigger);
	~MeshSwitcher();
	void setMesh(scene::ISceneNode* mesh);
	void update();
};

// SceneSwitcher : Observer
class IRRLICHT_API SceneSwitcher : public Switcher
{
private:
	ISceneSeamlessLoader* smgr;
public:
	SceneSwitcher(SwitchTrigger* trigger, scene::ISceneSeamlessLoader smgr);
	~SceneSwitcher();
	void setScene(int sceneIndex);
	void update();
};

} // end namespace video
} // end namespace irr