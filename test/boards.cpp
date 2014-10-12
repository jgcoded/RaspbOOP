#include <raspboop/Raspboop.h>

using rbp::L298N;
using rbp::WiringPiPins;

int main(int argc, char* argv[])
{
    rbp::Init();

    L298N controller(WiringPiPins::GPIO0,
                     WiringPiPins::GPIO1,
                     WiringPiPins::GPIO2,
                     WiringPiPins::GPIO3);

    controller.UseSoftPWM();

    controller.SetPWMValue(1, 50);
    controller.SetPWMValue(4, 50);

    return 0;
}
