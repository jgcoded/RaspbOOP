#include "raspboop/boards/L298N.h"
#include <pthread.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

using namespace std;

namespace rbp
{

L298N::L298N()
{
    mCommands.insert(std::make_pair("Set software PWM", SET_USE_PWM));
    mCommands.insert(std::make_pair("Set PWM Values", SET_PWM_VALUES));
    mCommands.insert(std::make_pair("Set Pin Values", SET_PIN_VALUES));
}

L298N::L298N(int in1, int in2, int in3, int in4) :
             mPins({in1, in2, in3, in4})
{
    ConsumePin(in1, OUTPUT);
    ConsumePin(in2, OUTPUT);
    ConsumePin(in3, OUTPUT);
    ConsumePin(in4, OUTPUT);
}

void L298N::UseSoftPWM()
{
    for(int i = 0; i < 4; ++i)
        if(softPwmCreate(mPins[i], 0, 100) != 0)
            cout << "Software PWM creation error: " << errno << endl;
}

void L298N::SetPWMValue(int in, int value)
{
    if(in < 1 || in > 4)
        return;

    int index = in - 1;

    // Wiringpi checks if Value is valid
    softPwmWrite(mPins[index], value);
}

void L298N::SetPinValue(int in, int value)
{
    if(in < 1 || in > 4)
        return;

    int index = in -1;

    digitalWrite(mPins[index], value);
}

void L298N::AcceptCommand(const Command& command)
{
    unsigned char commandId = command.GetCommandId();

    switch(commandId)
    {

        case SET_USE_PWM:
            UseSoftPWM();
        break;

        case SET_PWM_VALUES:
            for(int i = 1; i < 5; ++i)
                SetPWMValue(i, (int)command.GetParameterAtIndex(i - 1));
        break;

        case SET_PIN_VALUES:
            for(int i = 1; i < 5; ++i)
                SetPinValue(i, (int)command.GetParameterAtIndex(i - 1));
        break;

        default:
        break;
    }
}

std::map<std::string, unsigned char> L298N::GetCommands() const
{
    return mCommands;
}

const unsigned char L298N::GetComponentId() const
{
    return mComponentId;
}

void L298N::SetComponentId(unsigned char id)
{
    mComponentId = id;
}

std::vector<unsigned char> L298N::Serialize()
{
}

L298N::~L298N()
{
}

} /* rbp */
