#include "raspboop/Raspboop.h"

namespace rbp
{

L298N::L298N()
{
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
            printf("Software PWM creation error: %d\n", errno);
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


L298N::~L298N()
{
}

} /* rbp */
