#include <vector>
#include <irrlicht.h>

#pragma once
/**
 * IPathfinding
 * Interface for the pathfinding helper class.
 * To ensure that every pathfinding library can be used, there must be a helper class that inherits this interface
 * and encapsulates your pathfinding library.
 *
 * Note: We will use the library 'Recast' for pathfinding.
 */
class __declspec(dllexport) IPathfinding
{
public:
	virtual ~IPathfinding(void)
	{
	}

	virtual std::vector<irr::core::vector3df> returnPath(irr::core::vector3df *pStart, irr::core::vector3df *pEnd) = 0;
};

