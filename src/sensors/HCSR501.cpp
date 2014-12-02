#include "raspboop/Raspboop.h"

namespace rbp
{

HCSR501::HCSR501()
{
    mSignalPin = -1;
    mSignalled = false;
}

HCSR501::HCSR501(int signal) :
         mSignalPin(signal)
{
    SetInputPin(signal);
}

void HCSR501::Sense()
{
    mSignalled = digitalRead(mSignalPin) == 1;
}

HCSR501::~HCSR501()
{
}

} /* rbp */
