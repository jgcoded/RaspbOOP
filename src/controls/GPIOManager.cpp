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
namespace controls
{

GPIOManager::GPIOManager()
{
}

int GPIOManager::ReservePin(int Pin, int Mode)
{
	if(IsPinSet(Pin) != -1)
		return -1;

	GPIO.insert(std::pair<int, int>(Pin, Mode));

	return 1;
}

int GPIOManager::IsPinSet(int Pin)
{
	if(GPIO.count(Pin) == 0)
		return -1;

	return GPIO[Pin];
}

GPIOManager::~GPIOManager()
{
}

} /* controls */
} /* raspboop */
