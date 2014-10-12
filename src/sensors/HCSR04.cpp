#include "raspboop/Raspboop.h"
#include <exception>

namespace rbp
{

HCSR04::HCSR04() :
        mEchoPin(-1),
        mTriggerPin(-1),
        mEchoStart(0),
        mEchoEnd(0),
        mDistance(0)
{
}


HCSR04::HCSR04(int echo, int trig) :
        mEchoPin(echo),
        mTriggerPin(trig),
        mEchoStart(0),
        mEchoEnd(0),
        mDistance(0)
{

    // Using the same pins. Should notify user
    if(echo == trig)
        throw std::logic_error("Echo and trig pins are the same");

    SetInputPin(echo);
    SetOutputPin(trig);

    digitalWrite(trig, LOW);
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
