#include "raspboop/Raspboop.h"

namespace rbp
{

int Init(PinScheme scheme)
{

    // Setup wiringPi
    switch(scheme)
    {
        case PinScheme::GPIO:
            wiringPiSetupGpio();
        break;

        case PinScheme::SYS:
            wiringPiSetupSys();
        break;

        default:
            wiringPiSetup();
    }

    return 1;
}

int Deinit()
{
    /* nothing to deinit so far */
    return 1;
}

} /* rbp */
