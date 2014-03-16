#include <vector>
#include <irrlicht.h>

#pragma once
class IPathfinding
{
public:
	virtual ~IPathfinding(void)
	{
	}

	/**
	 * Returns the path from the start point to the end point
	 */
	virtual std::vector<irr::core::vector3df> returnPath(irr::core::vector3df *pStart, irr::core::vector3df *pEnd) = 0;
};

