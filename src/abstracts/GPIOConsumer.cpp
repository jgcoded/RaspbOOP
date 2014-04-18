#include "raspboop/Raspboop.h"

namespace raspboop
{

GPIOConsumer::GPIOConsumer()
{
}


void GPIOConsumer::ConsumePin(int Pin, int Mode)
{
    pinMode(Pin, Mode);
    Pins.push_back(Pin);
}


void GPIOConsumer::ReleasePins() const
{
    for(const int& Pin : Pins)
        pinMode(Pin, LOW);
}


GPIOConsumer::~GPIOConsumer()
{
    ReleasePins();
}

} /* raspboop */
