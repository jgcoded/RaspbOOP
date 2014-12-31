#include "raspboop/abstracts/Sensor.h"
#include <wiringPi.h>

namespace rbp
{

Sensor::Sensor()
{
}

void Sensor::SetOutputPin(int pin)
{
    ConsumePin(pin, OUTPUT);
}

void Sensor::SetInputPin(int pin)
{
    ConsumePin(pin, INPUT);
}

Sensor::~Sensor()
{
}

} /* rbp */
