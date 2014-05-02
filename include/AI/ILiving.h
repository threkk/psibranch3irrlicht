#pragma once

#include "ai/Detectable.h"

/**
 * ILiving
 * Interface for living classes, that can be hit by other classes
 */
class __declspec(dllexport) ILiving: virtual public Detectable
{
public:
	ILiving(void){};
	virtual ~ILiving(void){};

	/**
	 * Damages the object
	 */
	virtual void getHit(int damage) = 0;

	/**
	 * Checks if the object is knocked down
	 */
	virtual bool isKnockedDown() = 0;
};