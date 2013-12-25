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
namespace sensors
{

HCSR501::HCSR501()
{
	SignalPin = -1;
	Signalled = false;
}

HCSR501* HCSR501::Create(int SIGNAL)
{
	HCSR501* H = (HCSR501*)malloc(sizeof(HCSR501));

	// Not enough memory. Should notify user
	if(H == NULL)
		return NULL;

	new(H) HCSR501;

	H->SignalPin = SIGNAL;

	H->SetInputPin(SIGNAL);

	return H;
}

void HCSR501::Sense()
{
	Signalled = digitalRead(SignalPin);
}

void HCSR501::ReleasePins()
{
}

HCSR501::~HCSR501()
{
}

} /* sensors */
} /* raspboop */


