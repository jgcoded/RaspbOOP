#include "raspboop/Raspboop.h"

namespace rbp
{

L298N::L298N()
{
}


L298N* L298N::Create(int in1, int in2, int in3, int in4)
{

    L298N* L = (L298N*)malloc(sizeof(L298N));

    // Not enough memory. Should notify user
    if(L == NULL)
        return NULL;

    new (L) L298N;

    L->mPins[0] = in1;
    L->mPins[1] = in2;
    L->mPins[2] = in3;
    L->mPins[3] = in4;

    L->ConsumePin(in1, OUTPUT);
    L->ConsumePin(in2, OUTPUT);
    L->ConsumePin(in3, OUTPUT);
    L->ConsumePin(in4, OUTPUT);

    return L;
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
