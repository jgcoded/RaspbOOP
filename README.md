RaspbOOP
===========

A Raspberry Pi powered robot library with a code base dedicated to employing Object oriented programming practices geared towards abstracting electronic components, boards, and sensors - anything that can be interfaced through the Raspberry Pi's GPIO pins. 

Raspboop takes advantage of, and abstracts over, the amazing [WiringPi library](https://github.com/WiringPi/WiringPi) for its ease of use and stability.

Documentation
-------------

An integral part of Raspboop is documentation. [Checkout out this doc page](http://jgcoded.github.io/RaspbOOP-Bot/doc/html/classraspboop_1_1HCSR04.html#details) to get an idea of how Raspboop will make developing with sensors, boards, or any peripheral device that much easier.

An Example
==========

```cpp
#include <raspboop/Raspboop.h>
#include <iostream>
#include <map>

using namespace std;
using namespace rbp;

int main(int argc, char* argv[])
{
    rbp::Init();

    Server server;
    HCSR04 distanceSensor(WiringPiPins::GPIO0,
                          WiringPiPins::GPIO1);

    distanceSensor.SetComponentId(0);

    map<unsigned char, Commandable*> robotParts;

    robotParts.insert(make_pair(distanceSensor.GetComponentId(),
                                dynamic_cast<Commandable*>(&distanceSensor)));

    // Allow clients to find this robot automatically
    server.EnableAutodiscovery("0.0.0.0");

    server.AddCallback([&] (const Command* cmd, Server*) {

                            auto search =
                                    robotParts.find(cmd->GetComponentId());

                            if(search != robotParts.end())
                                search->second->AcceptCommand(*cmd);
                       });

    server.Start();
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
