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

#ifndef RASPBOOP_SENSORS_HCSR04_H
#define RASPBOOP_SENSORS_HCSR04_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

/*! \brief Ultrasonic distance sensor
 *
 * The HCSR04 is an ultrasonic distance sensor. By emitting an ultrasonic
 * sound, the distance between the sensor and another object can be
 * calculated through the formula:
 *
 * d = t * 340 /2
 *
 * where,
 * *d* is distance in meters,
 * *t* is time in seconds,
 * *340* is the speed of sound in m/s
 *
 * We divide by two because the sound had to travel back to the sensor.
 *
 * Helpful information
 * ===================
 *
 * - The sensor has 4 pins
 *		- **Vcc** input 5V here
 *		- **Trig** Input used to tell the sensor when to send the sound
 *		- **Echo** The output from the sensor
 *		- **GND** Connect this to ground
 *
 * **IMPORTANT INFORMATION:** The Raspberry Pi's pins operate at 3V3
 * 							  volt logic. This means that you must
 *							  use a voltage divider on the Echo pin
 *							  when reading in a value. I recommend
 *							  using two resistors whose values are
 *							  1.5x apart. For more detailed
 *							  instructions on how to do this, visit:
 * [bytecreation.com](http://www.bytecreation.com/blog/2013/10/13/
 *	raspberry-pi-ultrasonic-sensor-hc-sr04)
 *
 *  Quick Stats               |               Value
 * ---------------------------|------------------------------------
 * Operating Voltage          | **5V**
 * Operating Current          | **15 mA**
 * Soundwave frequency        | **40 Hz**
 * Maximum distance           | **4m**
 * Minimum distance           | **2 cm**
 * Required Trigger pulse     | **10us (microseconds) HIGH signal**
 * 
 *
 * External links
 * --------------
 *
 * [Datasheet](http://users.ece.utexas.edu/~valvano/Datasheets/
 * HCSR04b.pdf)
 *
 * [Blog post:](http://www.bytecreation.com/blog/2013/10/13/
 * raspberry-pi-ultrasonic-sensor-hc-sr04)
 * Good article that details the steps necessary to use this sensor
 * with a raspberry pi and a voltage divider.
 */
class HCSR04 : public Sensor
{

	int EchoPin;
	int TriggerPin;
	float EchoStart;
	float EchoEnd;
	float Distance;

public:

	/* \brief HCSR04 Constructor
	 *
	 * Initializes all private member variables to unused values.
	 */
    HCSR04();

    virtual void Sense();

    /*! \brief Get the distance calculated from the sensor
     *
     * \return A float representing the distance sensed in
     *		   centimeters
     */
    float GetDistance() const
	{
		return Distance;
	}

    virtual void ReleasePins();

    /*! \brief Create a usable HCSR04 object
     *
     * To properly create an object in raspboop, you must use its
	 * factory Create() method. The factory method initializes
	 * the HCSR04's pins using the SetInputPin() and 
	 * SetOutputPin() methods inherited from Sensor.
	 *
	 * \param ECHO The input pin designated to read the sensors ECHO
	 * 		  output
	 * \param TRIG The output pin that initiates sensing
	 *
	 * \return A pointer to an HCSR04 object with all pins initialized
     */
    static HCSR04* Create(int ECHO, int TRIG);

    /*! \brief HCSR04 Destructor
     */
    ~HCSR04();

};

} /* raspboop */

#endif /* RASPBOOP_SENSORS_HCSR04_H */
