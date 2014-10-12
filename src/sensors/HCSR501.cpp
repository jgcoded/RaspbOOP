#include "raspboop/Raspboop.h"

namespace rbp
{

HCSR501::HCSR501()
{
    mSignalPin = -1;
    mSignalled = false;
}


HCSR501* HCSR501::Create(int signal)
{
    HCSR501* H = (HCSR501*)malloc(sizeof(HCSR501));

    // Not enough memory. Should notify user
    if(H == NULL)
            return NULL;

    new(H) HCSR501;

    H->mSignalPin = signal;

    H->SetInputPin(signal);

    return H;
}


void HCSR501::Sense()
{
    mSignalled = digitalRead(mSignalPin);
}


HCSR501::~HCSR501()
{
}

} /* rbp */
