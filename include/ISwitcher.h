#include "ISceneNode.h"
#include "IQualityTexture.h"
#include "IAnimatedMeshSceneNode.h"
#include "ISceneSeamlessLoader.h";

using namespace irr;

namespace irr {
namespace video {
	
class Switcher 
{
private:
	SwitchTrigger trigger;
public:
	Switcher(SwitchTrigger trigger);
	~Switcher();
	virtual void switchElement()=0;
	virtual bool isClose(scene::ISceneNode* node)=0;
	virtual bool isClose(core::vector3df position)=0;
};

class IRRLICHT_API SwitchTrigger
{
	SwitchTrigger(scene::ISceneNode* node);
	~SwitchTrigger();
	bool isClose(scene::ISceneNode* node);
	bool isClose(core::vector3df position);
};

class IRRLICHT_API TextureSwitcher : public Switcher
{
private:
	IQualityTexture texture;
public:
	TextureSwitcher(SwitchTrigger trigger);
	~TextureSwitcher();
	void setTexture(IQualityTexture* texture);
};

class IRRLICHT_API MeshSwitcher : public Switcher
{
private:
	ISceneNode* mesh;
public:
	MeshSwitcher(SwitchTrigger trigger);
	~MeshSwitcher();
	void setMesh(scene::ISceneNode* mesh);
};

class IRRLICHT_API SceneSwitcher : public Switcher
{
private:
	ISceneSeamlessLoader smgr;
public:
	SceneSwitcher(SwitchTrigger trigger);
	~SceneSwitcher();
	void setScene(scene::ISceneSeamlessLoader smgr);

} // end namespace video
} // end namespace irr