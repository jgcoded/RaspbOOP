#include "raspboop/sensors/HCSR04.h"
#include <exception>
#include <wiringPi.h>
#include <stdexcept>

namespace rbp
{

HCSR04::HCSR04(int echo, int trig) :
        mEchoPin(echo),
        mTriggerPin(trig),
        mEchoStart(0),
        mEchoEnd(0),
        mDistance(0)
{

    mCommands.insert(std::make_pair("Sense distance", SENSE));

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

void HCSR04::AcceptCommand(const Command& command)
{
    unsigned char commandId = command.GetCommandId();

    switch(commandId)
    {

        case SENSE:
            Sense();
        break;

        default:
        break;
    }
}

std::map<std::string, unsigned char> HCSR04::GetCommands()
{
    return mCommands;
}

unsigned char HCSR04::GetComponentId()
{
    return mComponentId;
}

void HCSR04::SetComponentId(unsigned char id)
{
    mComponentId = id;
}

std::vector<unsigned char> HCSR04::Serialize()
{

}

HCSR04::~HCSR04()
{
}

} /* rbp */
