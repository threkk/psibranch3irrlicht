#pragma once

#include "ai/Detectable.h"

/**
* ILiving
* Interface for living things, that can be hit
*/
class __declspec(dllexport) ILiving: virtual public Detectable
{
public:
	ILiving(void){};
	virtual ~ILiving(void){};

	virtual void getHit(int damage) = 0;
	virtual bool isKnockedDown() = 0;
};