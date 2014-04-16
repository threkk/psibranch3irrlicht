#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include "ai/StateMachine.h"
#include <functional>

#pragma once
class __declspec(dllexport) StateInvestigatePoint : public State
{
public:
	StateInvestigatePoint(Detectable* stateOwner, irr::core::vector3df* point, float attentionSpan, float visionLength,
		irr::scene::ISceneManager* sceneManager, irr::IrrlichtDevice* device, std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction, 
		IPathfinding* pathUtil, StateMachine* stateMachine);
	~StateInvestigatePoint(void);

	/** Inherited methods **/
	bool executeable(void);
	void enter();
	void exit();
protected:
	// The owner of the state
	Detectable* stateOwner;

	// The point to visit
	irr::core::vector3df point;

	// The state machine
	StateMachine* stateMachine;

	// The pathfinding utility
	IPathfinding* pathUtil;

	// The callback function
	std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction;

	// How long state owner should look at point
	float attentionSpan;
	// From what distance state owner can see the point
	float visionLength;

	// Irrlicht scene manager
	irr::scene::ISceneManager* sceneManager;

	// Irrlicht device
	irr::IrrlichtDevice* device;

	// Timer stuff
	irr::u32 now;
	irr::u32 then;
	irr::f32 frameDeltaTime;
	irr::f32 timer;

	void updateDeltaTime();

	/** Overwritten methods **/
	void action();
};