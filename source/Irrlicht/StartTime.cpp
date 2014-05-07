#include "StartTime.h"

using namespace irr;

StartTime::StartTime()
{
	device->getTimer();
	std::cout << "Time: " << device->getTimer() << std::endl;
}

StartTime::~StartTime(void)
{
}