#include "raspboop/Raspboop.h"

namespace raspboop
{

int Init(PinScheme Scheme)
{

    // Setup wiringPi
    switch(Scheme)
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

} /* raspboop */
