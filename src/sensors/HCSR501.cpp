#include "raspboop/sensors/HCSR501.h"
#include <wiringPi.h>

namespace rbp
{

HCSR501::HCSR501()
{
    mSignalPin = -1;
    mSignalled = false;

    mCommands.insert(std::make_pair("Sense movement", SENSE));
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

void HCSR501::AcceptCommand(const Command& command)
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

std::map<std::string, unsigned char> HCSR501::GetCommands() const
{
    return mCommands;
}

const unsigned char HCSR501::GetComponentId() const
{
    return mComponentId;
}

void HCSR501::SetComponentId(unsigned char id)
{
    mComponentId = id;
}

std::vector<unsigned char> HCSR501::Serialize()
{

}

HCSR501::~HCSR501()
{
}

} /* rbp */
