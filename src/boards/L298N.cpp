#include "raspboop/Raspboop.h"

namespace raspboop
{

L298N::L298N()
{
}

L298N* L298N::Create(int IN1, int IN2, int IN3, int IN4)
{

	L298N* L = (L298N*)malloc(sizeof(L298N));

	// Not enough memory. Should notify user
	if(L == NULL)
		return NULL;

	L->Pins[0] = IN1;
	L->Pins[1] = IN2;
	L->Pins[2] = IN3;
	L->Pins[3] = IN4;

	L->ConsumePin(IN1, OUTPUT);
	L->ConsumePin(IN2, OUTPUT);
	L->ConsumePin(IN3, OUTPUT);
	L->ConsumePin(IN4, OUTPUT);

	return L;
}

void L298N::UseSoftPWM()
{
	for(int i = 0; i < 4; ++i) {
		if(softPwmCreate(Pins[i], 0, 100) != 0) {
			// error occurred
			printf("Software PWM creation error: %d\n", errno);
		}
	}
}

void L298N::SetPWMValue(int IN, int Value)
{
	if(IN < 1 || IN > 4)
		return;

	int index = IN - 1;

	// Wiringpi checks if Value is valid
	softPwmWrite(Pins[index], Value);
}

void L298N::SetPinValue(int IN, int Value)
{
	if(IN < 1 || IN > 4)
		return;

	int index = IN -1;

	digitalWrite(Pins[index], Value);
}

L298N::~L298N()
{
}

} /* raspboop */
