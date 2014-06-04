#include "ISceneNode.h"
#include "IAnimatedMeshSceneNode.h"
#include "ISceneSeamlessLoader.h";
#include <vector>

using namespace irr;

namespace irr {
namespace video {

/**
 * The SwitchTrigger class in combination with the Switcher class and its
 * children provide the tools needed for automatically generate changes in the
 * scene based on node's positions and triggers.
 *
 * The SwitchTrigger class assigns a trigger to a ISceneNode element on the map.
 * Later, the developer attaches different switchers to the trigger. More than
 * one switcher can be attached per trigger, and each switcher can refer to a
 * different element in the scene or even different scenes.
 *
 * The trigger is fired when the distance between the reference element of the
 * trigger and a position or other node assigned to the switcher is less or equal
 * than the triggering distance. Different positions or nodes can be set for 
 * different switchers.
 *
 * The sequence is:
 * 1. Create a trigger.
 * 2. Attach a ISceneNode to the trigger.
 * 3. Attach different switchers to the trigger.
 * 4. Check when the distance between the trigger and any other position or node
 *    is less or equal than the triggering distance. Then all the switchers will
 *    be fired.
 */

/**
 *SwitchTrigger : Observablei
 */
class IRRLICHT_API SwitchTrigger
{
private:
    //! Reference node
	scene::ISceneNode* node;
    //! Vector with all the switchers attached to the node.
	std::vector <class Switcher *> switchers;
public:
    // ! Triggering distance. Fired when less or equal. Set as public on purpose.
	double triggeringDistance;
    /**
     * Constructor.
     * \param referenceNode The node that will be set as reference for the trigger
     *  and all the switchers attached to it.
     */
	SwitchTrigger(scene::ISceneNode* referenceNode);
	/**
     * Destructor
     */
    ~SwitchTrigger();
    /**
     * Attaches the switchers to the trigger.
     * \param swt Pointer to the switcher.
     */
	void attach(Switcher* swt);
	/**
     * Function called when the switcher is fired. Set as public in case the 
     * developer wants to create his owns firing conditions.
     */
    void notify();
    /**
     * Checks if the reference node is close to the parameter node.
     * \param other The other node.
     * \return true if the distance is equal or less than the triggering distance.
     */
	bool isClose(scene::ISceneNode* other);
    /**
     * Checks if the reference node is close to the location.
     * \param position The position to check distance.
     * \return true if the distance is equal or less than the triggering distance.
     */
	bool isClose(core::vector3df position);
};

/**
 * Switcher : Parent observer. Abstract class.
 */
class Switcher 
{
private:
    //! Trigger that the switcher is attached to.
	SwitchTrigger* trigger;
public:
    /**
     * Checks if the switcher is activated or not.
     */
	bool active;
    /**
     * Constructor.
     * \param trg Trigger to be attached to.
     */
	Switcher(SwitchTrigger* trg);
	/**
     * Destructor.
     */
    ~Switcher();
    /**
     * Function that will be called when the trigger is fired. Virtual function.
     */
	virtual void update()=0;
};

/**
 * TextureSwitcher : Observer. Child of Switcher. Changes textures of a model.
 */
class IRRLICHT_API TextureSwitcher : public Switcher
{
private:
    //! Texture to switch to.
	IQualityTexture* texture;
	u32 textureLayer;
    //! Node to apply the texture change.
	scene::ISceneNode* node;
public:
    /**
     * Constructor.
     * \param trigger Trigger that is attached to.
     * \param dst Node to apply the texture change.
     */
	TextureSwitcher(SwitchTrigger* trigger, scene::ISceneNode* dst);
	/**
     * Destructor.
     */
    ~TextureSwitcher();
	/**
     * Sets the texture to change to.
     * \param textureLayer Texture layer.
     * \param texture IQualityTexture to change to.
     */
    void setTexture(u32 textureLayer, IQualityTexture* texture);
    /**
     * Sets the texture to change to.
     * \param textureLayer Texture layer.
     * \param texture ITexture to change to.
     */
	void setTexture(u32 textureLayer, ITexture* texture);
    /**
     * Called when the trigger is fired. It makes the change of the texture.
     */
	void update();
};
/**
 * SceneSwitcher : Observer. Child of Switcher. Changes the scene.
 */
class IRRLICHT_API SceneSwitcher : public Switcher
{
private:
    //! ISceneSeamlessLoader that contains the scenes to change to.
	ISceneSeamlessLoader* smgr;
    //! Scene index to change to.
	int sceneIndex;
public:
     /**
     * Constructor.
     * \param trigger Trigger that is attached to.
     * \param smgr SceneManager that changes the scenes.
     */
	SceneSwitcher(SwitchTrigger* trigger, scene::ISceneSeamlessLoader* smgr);
	/**
     * Destructor.
     */
    ~SceneSwitcher();
    /**
     * Changes the scene.
     * \param sceneIndex The index of the scene to change.
     */
	void setScene(int sceneIndex);
    /**
     * Called when the trigger is fired. It makes the change of the texture.
     */
	void update();
};

//! Work in progress. Waiting for the Mesh Switcher.
//! MeshSwitcher : Observer
/*class IRRLICHT_API MeshSwitcher : public Switcher
{
private:
	ISceneNode* mesh;
public:
	MeshSwitcher(SwitchTrigger* trigger);
	~MeshSwitcher();
	void setMesh(scene::ISceneNode* mesh);
	void update();
};*/

} // end namespace video
} // end namespace irr
