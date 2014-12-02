#include "raspboop/Raspboop.h"

namespace rbp
{

GPIOConsumer::GPIOConsumer()
{
}

void GPIOConsumer::ConsumePin(int pin, int mode)
{
    pinMode(pin, mode);
    mPins.push_back(pin);
}

void GPIOConsumer::ReleasePins() const
{
    for(const int& pin : mPins)
        pinMode(pin, LOW);
}

GPIOConsumer::~GPIOConsumer()
{
    ReleasePins();
}

} /* rbp */
