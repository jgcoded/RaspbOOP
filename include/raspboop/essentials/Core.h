#ifndef RASPBOOP_ESSENTIALS_CORE_H
#define RASPBOOP_ESSENTIALS_CORE_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

/*! \brief The GPIO pin numbering scheme to use
 *
 * see Init();
 */
enum class PinScheme
{
    WIRING = 0,
    GPIO = 1,
    SYS = 2
};

/*! \brief A convenience enum for the P1 GPIO Connector pins
 *  [Pin reference](http://wiringpi.com/pins/)
 */
enum WiringPiPins
{
    GPIO0 = 0,
    GPIO1 = 1,
    GPIO2 = 2,
    GPIO3 = 3,
    GPIO4 = 4,
    GPIO5 = 5,
    GPIO6 = 6,
    GPIO7 = 7,
    SDA = 8,
    SCL = 9,
    CE0 = 10,
    CE1 = 11,
    MOSI = 12,
    MISO = 13,
    SCLK = 14,
    TxD = 15,
    RxD = 16     
};

/*! \brief A BCM GPIO convenience enum for Revision 1/model A Raspberry Pi's
 * [Pin reference](http://wiringpi.com/pins/)
 */
enum BCMPinsRev1
{
    GPIO0 = 17,
    GPIO1 = 18,
    GPIO2 = 21, // Model A specific
    GPIO3 = 22,
    GPIO4 = 23,
    GPIO5 = 24,
    GPIO6 = 25,
    GPIO7 = 4,
    SDA = 0,    // Model A specific
    SCL = 1,    // Model A specific
    CE0 = 8,
    CE1 = 7,
    MOSI = 10,
    MISO = 9,
    SCLK = 11,
    TxD = 14,
    RxD = 15
};

/*! \brief A BCM GPIO convenience enum for Revision 2/model B Raspberry Pi's
 * [Pin reference](http://wiringpi.com/pins/)
 */
enum BCMPinsRev2
{
    GPIO0 = 17,
    GPIO1 = 18,
    GPIO2 = 27, // Model B specific
    GPIO3 = 22,
    GPIO4 = 23,
    GPIO5 = 24,
    GPIO6 = 25,
    GPIO7 = 4,
    SDA = 2,    // Model B specific
    SCL = 3,    // Model B specific
    CE0 = 8,
    CE1 = 7,
    MOSI = 10,
    MISO = 9,
    SCLK = 11,
    TxD = 14,
    RxD = 15
};

/*! \brief A convenience enum for the P5 connector on the Raspberry Pi Model B
 * This enum is specific to the WiringPi pin numbering
 * [Pin reference](http://wiringpi.com/pins/)
 */
enum WiringPiPinsP5
{
    GPIO8 = 17,
    GPIO9 = 18,
    GPIO10 = 19,
    GPIO11 = 20
};

/*! \brief a convenience enum for the P5 connector on the Raspberry Pi Model B
 * This enum is specific to the BCM GPIO pin numbering
 * [Pin reference](http://wiringpi.com/pins/)
 */
enum BCMPinsP5
{
    GPIO8 = 28,
    GPIO9 = 29,
    GPIO10 = 30,
    GPIO11 = 31
};

/*! \brief Initializes Raspboop and its dependencies
 *
 * Initializes raspboop and wiringPi. The pin numbering
 * scheme used depends on the value passed into the
 * Scheme parameter.
 *
 * see PinScheme for the available schemes, and visit
 * the [wiringPi reference](http://wiringpi.com/reference/
 * setup/) for a detailed description of the implications
 * of a pin scheme. The default pin scheme is Wiring.
 *
 * \param Scheme The pin scheme to use.
 */
int Init(PinScheme Scheme = PinScheme::WIRING);

/*! \todo Implement Deinit() method */
int Deinit();

} /* raspboop */

#endif /* RASPBOOP_ESSENTIALS_CORE_H */
