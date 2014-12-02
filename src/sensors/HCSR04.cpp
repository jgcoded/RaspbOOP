#include "raspboop/Raspboop.h"

namespace raspboop
{

HCSR04::HCSR04()
{
    EchoPin = -1;
    TriggerPin = -1;
    EchoStart = 0;
    EchoEnd = 0;
    Distance = 0;
}


HCSR04* HCSR04::Create(int e, int t)
{

    // Using the same pins. Should notify user
    if(e == t)
        return NULL;

    HCSR04* H = (HCSR04*)malloc(sizeof(HCSR04));

    // Not enough memory. Should notify user
    if(H == NULL)
        return NULL;

    new(H) HCSR04;

    H->EchoPin = e;
    H->TriggerPin = t;

    H->SetInputPin(e);
    H->SetOutputPin(t);

    digitalWrite(t, LOW);

    return H;
}


void HCSR04::Sense()
{
    // Pins are not set, should notify user
    if(EchoPin == -1 || TriggerPin == -1)
            return;

    EchoStart = EchoEnd = 0;

    digitalWrite(TriggerPin, HIGH);
    // HCSR04 manual states to wait 10 micros when triggered
    delayMicroseconds(10);
    digitalWrite(TriggerPin, LOW);

    while(digitalRead(EchoPin) == 0)
        EchoStart = (float)micros();

    while(digitalRead(EchoPin))
        EchoEnd = (float)micros();

    Distance = (EchoEnd - EchoStart) * .017f;
}


HCSR04::~HCSR04()
{
}

} /* raspboop */
