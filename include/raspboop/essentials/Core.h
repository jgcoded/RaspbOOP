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

#define PIN(x, y) \
        static const int (x) = (y);

/*! \brief A convenience class for the P1 GPIO Connector pins
 *  [Pin reference](http://wiringpi.com/pins/)
 */
class WiringPiPins
{
    
public:
    
    PIN(GPIO0,  0)
    PIN(GPIO1,  1)
    PIN(GPIO2,  2)
    PIN(GPIO3,  3)
    PIN(GPIO4,  4)
    PIN(GPIO5,  5)
    PIN(GPIO6,  6)
    PIN(GPIO7,  7)
    PIN(SDA  ,  8)
    PIN(SCL  ,  9)
    PIN(CE0  , 10)
    PIN(CE1  , 11)
    PIN(MOSI , 12)
    PIN(MISO , 13)
    PIN(SCLK , 14)
    PIN(TxD  , 15)
    PIN(RxD  , 16)
};

/*! \brief A BCM GPIO convenience class for Revision 1/model A Raspberry Pi's
 * [Pin reference](http://wiringpi.com/pins/)
 */
class BCMPinsRev1
{
    
public:
    
    PIN(GPIO0, 17)
    PIN(GPIO1, 18)
    PIN(GPIO2, 21)    // Model A specific
    PIN(GPIO3, 22)
    PIN(GPIO4, 23)
    PIN(GPIO5, 24)
    PIN(GPIO6, 25)
    PIN(GPIO7,  4)
    PIN(SDA  ,  0)    // Model A specific
    PIN(SCL  ,  1)    // Model A specific
    PIN(CE0  ,  8)
    PIN(CE1  ,  7)
    PIN(MOSI , 10)
    PIN(MISO ,  9)
    PIN(SCLK , 11)
    PIN(TxD  , 14)
    PIN(RxD  ,  1)
};

/*! \brief A BCM GPIO convenience class for Revision 2/model B Raspberry Pi's
 * [Pin reference](http://wiringpi.com/pins/)
 */
class BCMPinsRev2
{
    
public:
    
    PIN(GPIO0, 17)
    PIN(GPIO1, 18)
    PIN(GPIO2, 27)    // Model B specific
    PIN(GPIO3, 22)
    PIN(GPIO4, 23)
    PIN(GPIO5, 24)
    PIN(GPIO6, 25)
    PIN(GPIO7,  4)
    PIN(SDA  ,  2)    // Model B specific
    PIN(SCL  ,  3)    // Model B specific
    PIN(CE0  ,  8)
    PIN(CE1  ,  7)
    PIN(MOSI , 10)
    PIN(MISO ,  9)
    PIN(SCLK , 11)
    PIN(TxD  , 14)
    PIN(RxD  ,  1)
};

/*! \brief A convenience class for the P5 connector on the Raspberry Pi Model B
 * This class is specific to the WiringPi pin numbering
 * [Pin reference](http://wiringpi.com/pins/)
 */
class WiringPiPinsP5
{
    
public:
    
    PIN(GPIO8 , 17)
    PIN(GPIO9 , 18)
    PIN(GPIO10, 19)
    PIN(GPIO11, 20)
};

/*! \brief a convenience class for the P5 connector on the Raspberry Pi Model B
 * This class is specific to the BCM GPIO pin numbering
 * [Pin reference](http://wiringpi.com/pins/)
 */
class BCMPinsP5
{
    
public:
    
    PIN(GPIO8 , 28)
    PIN(GPIO9 , 29)
    PIN(GPIO10, 30)
    PIN(GPIO11, 31)
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
