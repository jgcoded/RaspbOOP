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

#ifndef RASPBOOP_INTERFACES_SENSOR_H
#define RASPBOOP_INTERFACES_SENSOR_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

/*! \brief An abstract class for devices that can interface with the world
 *
 * Sensors can sense the world and provide valuable data about the
 * state of the current environment. 
 * 
 * Most sensors require an output, or a trigger, GPIO pin that tells
 * the sensor when to sense. An example of this type of sensor is the
 * [HCSR04](@ref HCSR04) ultrasonic distance sensor. However, there
 * are sensors that persistently report its value back to a GPIO
 * pin. An example of this type of sensor is the
 * [HCSR501](@ref HCSR501) passive infrared sensor.
 *
 * In both cases, there is a need for either an output pin and/or
 * an input pin.
 */
class Sensor : public GPIOConsumer
{

protected:

	/*! \brief Set an output pin for the sensor
	 *
	 * Consumes a pin to be designated as an output. This is usually
	 * the pin that triggers sensing.
	 *
	 * \param Pin The pin to designate as an output
	 */
	void SetOutputPin(int Pin);

	/*! \brief Set an input pin for the sensor
	 *
	 * Consumes a pin to be designated as an input. This is usually
	 * the pin that will be receiving data from the sensor.
	 *
	 * \param Pin The pin to designate as in input
	 */
	void SetInputPin(int Pin);

public:

    Sensor();

    /*! \brief Performs the sensor's sensing operation
     *
     * This method will retrieve a value from the environment
     * by performing GPIO operations on the input and output
     * pins of the sensor. The value from the sensor will be 
     * available through an accessor method.
     */
    virtual void Sense()=0;

    virtual ~Sensor()=0;

}; /* Sensor */

} /* raspboop */

#endif /* RASPBOOP_INTERFACES_SENSOR_H */
