#include <raspboop/Raspboop.h>

using rbp::L298N;
using rbp::WiringPiPins;

int main(int argc, char* argv[])
{
    rbp::Init();

    L298N* Controller = L298N::Create(WiringPiPins::GPIO0,
                                      WiringPiPins::GPIO1,
                                      WiringPiPins::GPIO2,
                                      WiringPiPins::GPIO3);

    Controller->UseSoftPWM();

    Controller->SetPWMValue(1, 50);
    Controller->SetPWMValue(4, 50);

    delete Controller;

    return 0;
}
