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

using raspboop::HCSR04;
using raspboop::HCSR501;

int main(int argc, char* argv[])
{

#define SIG 6
#define TRIG 4
#define ECHO 5

    raspboop::Init(raspboop::WIRING);

    bool ShouldRun = true;
    HCSR04* DistanceSensor = HCSR04::Create(ECHO, TRIG);
    HCSR501* InfraredSensor = HCSR501::Create(SIG);

    while(ShouldRun)
    {

        InfraredSensor->Sense();
        DistanceSensor->Sense();

        int Motion = InfraredSensor->IsSignalled();
        float Distance = DistanceSensor->GetDistance();

        printf("Motion Detected: %d", Motion);
        printf("Distance: %0.2f centimeters", Distance);

        if(Distance < 20.0f)
            ShouldRun = false;
        else
            delay(1000);
    }

    delete InfraredSensor;
    delete DistanceSensor;

    return 0;
}
