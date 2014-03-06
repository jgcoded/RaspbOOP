/* *
* Copyright (c) 2013 Julio Gutierrez
* 
* Permission is hereby granted, free of charge, to any person obtaining a co$
* this software and associated documentation files (the "Software"), to deal$
* the Software without restriction, including without limitation the rights $
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell cop$
* the Software, and to permit persons to whom the Software is furnished to d$
* subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in$
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, F$
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHOR$
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHE$
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
* */

#ifndef RASPBOOP_ABSTRACTS_GPIOCONSUMER_H
#define RASPBOOP_ABSTRACTS_GPIOCONSUMER_H

#include "raspboop/Raspboop.h"

namespace raspboop
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

protected:

	/*! \brief Reserves a pin and sets its mode
	 *
	 * Uses wiringPi's *pinMode()* method to set the value of the *Pin* to
	 * the *Mode* parameter.
	 *
	 * \param Pin the GPIO pin to set
	 * \param Mode The Mode the Pin will be set to
	 */
	void ConsumePin(int Pin, int Mode) const;

	 /*! \brief Sets the mode of all pins to an inactive state
     *
     * All children must call this method when it becomes out of scope,
     * preferably in the destructor. This is necessary so that there are
     * never any GPIO pins unnecessarily set to *HIGH*
     */
    virtual void ReleasePins()=0;

public:

    GPIOConsumer();
    
    virtual ~GPIOConsumer()=0;

}; /* GPIOConsumer */

} /* raspboop */

#endif /* RASPBOOP_ABSTRACTS_GPIOCONSUMER_H */
