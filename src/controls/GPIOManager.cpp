#include "raspboop/Raspboop.h"

namespace raspboop
{

GPIOManager::GPIOManager()
{
}

int GPIOManager::ReservePin(int Pin, int Mode)
{
	if(GPIO.count(Pin) != 0)
		return -1;

	GPIO.insert(std::pair<int, int>(Pin, Mode));

	return 1;
}

int GPIOManager::IsPinSet(int Pin)
{
	if(GPIO.count(Pin) == 0)
		return -1;

	return GPIO[Pin];
}

GPIOManager::~GPIOManager()
{
}

} /* raspboop */
