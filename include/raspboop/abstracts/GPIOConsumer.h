#ifndef RASPBOOP_ABSTRACTS_GPIOCONSUMER_H
#define RASPBOOP_ABSTRACTS_GPIOCONSUMER_H

#include "raspboop/Raspboop.h"
#include <vector>

namespace rbp
{

/*! \brief Abstract class for all GPIO pin utilizers
 *
 * If a class will interface with the Raspberry Pi's GPIO pins, then it must
 * inherit from this class. This is to ensure that all children will be
 * forced to use the `ReleasePins()` method, which sets the value
 * of any active pins to an inactive state.
 *
 * Also, the `ConsumePin()` method provides a layer of abstraction over the
 * wiringPi `pinMode()` method. In the future, this method will be a friend
 * of the [GPIOManager](@ref GPIOManager) class.
 */
class GPIOConsumer
{
    std::vector<int> mPins;

    /*! \brief Sets the mode of all pins to an inactive state
     *
     * All children must call this method when it becomes out of scope,
     * preferably in the destructor. This is necessary so that there are
     * never any GPIO pins unnecessarily set to *HIGH*
     */
    virtual void ReleasePins() const;

protected:

    /*! \brief Reserves a pin and sets its mode
     *
     * Uses wiringPi's *pinMode()* method to set the value of the *Pin* to
     * the *Mode* parameter.
     *
     * \param Pin the GPIO pin to set
     * \param Mode The Mode the Pin will be set to
     */
    void ConsumePin(int pin, int mode);

public:

    GPIOConsumer();

    std::vector<int> GetPins() const { return mPins; }

    virtual ~GPIOConsumer()=0;

}; /* GPIOConsumer */

} /* rbp */

#endif /* RASPBOOP_ABSTRACTS_GPIOCONSUMER_H */
