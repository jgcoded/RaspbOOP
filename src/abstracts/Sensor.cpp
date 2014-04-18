#include "raspboop/Raspboop.h"

namespace raspboop
{

Sensor::Sensor()
{
}


void Sensor::SetOutputPin(int Pin)
{
    ConsumePin(Pin, OUTPUT);
}


void Sensor::SetInputPin(int Pin)
{
    ConsumePin(Pin, INPUT);
}


Sensor::~Sensor()
{
}

} /* raspboop */
