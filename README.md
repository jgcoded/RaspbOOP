RaspbOOP
===========

A Raspberry Pi powered robot library with a code base dedicated to employing Object oriented programming practices geared towards abstracting electronic components, boards, and sensors - anything that can be interfaced through the Raspberry Pi's GPIO pins. 

Raspboop takes advantage of, and abstracts over, the amazing [WiringPi library](https://github.com/WiringPi/WiringPi) for its ease of use and stability.

Documentation
-------------

An integral part of Raspboop is documentation. [Checkout out this doc page](http://jgcoded.github.io/RaspbOOP/doc/html/classraspboop_1_1HCSR04.html#details) to get an idea of how Raspboop will make developing with sensors, boards, or any peripheral device that much easier.

An Example
==========

```cpp
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
```

Building & Contributing
=======================

RaspbOOP-Bot uses **CMake** to generate the necessary build files. You can also generate build files for your preferred IDE/Compiler.

You will also need a **Raspberry Pi**, although it is recommended to develop on your preferred *nix platform, and then test new code on the Raspberry Pi.
Raspboop automatically downloads and uses the newest version of wiringPi for you.

You will also need **git**.

Licensing
=========
Unless otherwise stated, all files and all subsequent files relative to the path of this README are licensed under
***The MIT License (MIT)***. A copy of THE MIT License (MIT) can be found in the same directory as the README.
