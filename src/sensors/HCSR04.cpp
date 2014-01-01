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

HCSR04::HCSR04()
{
	EchoPin = -1;
	TriggerPin = -1;
	EchoStart = 0;
	EchoEnd = 0;
	Distance = 0;
}

HCSR04* HCSR04::Create(int ECHO, int TRIG)
{

	// Using the same pins. Should notify user
	if(ECHO == TRIG)
		return NULL;

	HCSR04* H = (HCSR04*)malloc(sizeof(HCSR04));

	// Not enough memory. Should notify user
	if(H == NULL)
		return NULL;

	new(H) HCSR04;

	H->EchoPin = ECHO;
	H->TriggerPin = TRIG;

	H->SetInputPin(ECHO);
	H->SetOutputPin(TRIG);

	digitalWrite(TRIG, LOW);

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

void HCSR04::ReleasePins()
{
	digitalWrite(TriggerPin, LOW);
}

HCSR04::~HCSR04()
{
	ReleasePins();
}

} /* raspboop */
