#include <raspboop/Raspboop.h>
#include <iostream>
#include <map>

using namespace std;
using namespace rbp;

int main(int argc, char* argv[])
{
    Server server;
    HCSR04 distanceSensor(WiringPiPins::GPIO0,
                          WiringPiPins::GPIO1);

    distanceSensor.SetComponentId(0);

    map<unsigned char, Commandable*> robotParts;
    robotParts.insert(make_pair(distanceSensor.GetComponentId(),
                                &distanceSensor));

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
