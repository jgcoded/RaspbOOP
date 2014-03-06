#include "raspboop/Raspboop.h"

namespace raspboop
{

GPIOConsumer::GPIOConsumer()
{
}

void GPIOConsumer::ConsumePin(int Pin, int Mode) const
{
	pinMode(Pin, Mode);
}

GPIOConsumer::~GPIOConsumer()
{
}

} /* raspboop */
