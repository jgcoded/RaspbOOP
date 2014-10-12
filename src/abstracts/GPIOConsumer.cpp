#include "raspboop/Raspboop.h"

namespace rbp
{

GPIOConsumer::GPIOConsumer()
{
}


void GPIOConsumer::ConsumePin(int pin, int mode)
{
    pinMode(pin, mode);
    Pins.push_back(pin);
}


void GPIOConsumer::ReleasePins() const
{
    for(const int& pin : Pins)
        pinMode(pin, LOW);
}


GPIOConsumer::~GPIOConsumer()
{
    ReleasePins();
}

} /* rbp */
