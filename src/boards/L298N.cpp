/* *
* Copyright (c) 2013 Julio Gutierrez
* 
* Permission is hereby granted, free of charge, to any person obtaining a co$
* this software and associated documentation files (the "Software"), to deal$
* the Software without restriction, including without limitation the rights $
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell cop$
* the Software, and to permit persons to whom the Software is furnished to d$
* subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in$
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, F$
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHOR$
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHE$
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
* */

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
	L->Pins[3] = IN3;
	L->Pins[4] = IN4;

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
}

void L298N::ReleasePins()
{
	for(int i = 0; i < 4; ++i)
		digitalWrite(Pins[i], LOW);
}

L298N::~L298N()
{
}

} /* raspboop */
