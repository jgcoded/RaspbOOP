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

#include <stdio.h>
#include <raspboop/Raspboop.h>

using raspboop::L298N;

int main(int argc, char* argv[])
{

#define IN1 23
#define IN2 24
#define IN3 3
#define IN4 4


	raspboop::Init(0);
	L298N* Controller = L298N::Create(IN1, IN2, IN3, IN4);

	Controller->UseSoftPWM();

	Controller->SetPWMValue(1, 50);
	Controller->SetPWMValue(4, 50);

	Controller->ReleasePins();

	delete Controller;

	return 0;
}
