#include "raspboop/Raspboop.h"

namespace raspboop
{

int Init(int Scheme)
{

    // Setup wiringPi
    switch(Scheme)
    {
        case GPIO:
            wiringPiSetupGpio();
        break;

        case SYS:
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
