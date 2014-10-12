#include "raspboop/Raspboop.h"

namespace rbp
{

HCSR04::HCSR04()
{
    mEchoPin = -1;
    mTriggerPin = -1;
    mEchoStart = 0;
    mEchoEnd = 0;
    mDistance = 0;
}


HCSR04* HCSR04::Create(int echo, int trig)
{

    // Using the same pins. Should notify user
    if(echo == trig)
        return NULL;

    HCSR04* H = (HCSR04*)malloc(sizeof(HCSR04));

    // Not enough memory. Should notify user
    if(H == NULL)
        return NULL;

    new(H) HCSR04;

    H->mEchoPin = echo;
    H->mTriggerPin = trig;

    H->SetInputPin(echo);
    H->SetOutputPin(trig);

    digitalWrite(trig, LOW);

    return H;
}


void HCSR04::Sense()
{
    // Pins are not set, should notify user
    if(mEchoPin == -1 || mTriggerPin == -1)
            return;

    mEchoStart = mEchoEnd = 0;

    digitalWrite(mTriggerPin, HIGH);
    // HCSR04 manual states to wait 10 micros when triggered
    delayMicroseconds(10);
    digitalWrite(mTriggerPin, LOW);

    while(digitalRead(mEchoPin) == 0)
        mEchoStart = (float)micros();

    while(digitalRead(mEchoPin))
        mEchoEnd = (float)micros();

    mDistance = (mEchoEnd - mEchoStart) * .017f;
}


HCSR04::~HCSR04()
{
}

} /* rbp */
