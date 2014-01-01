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

#ifndef RASPBOOP_SENSORS_HCSR501_H
#define RASPBOOP_SENSORS_HCSR501_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

/*! \brief Passive infrared sensor for motion detection
 *
 * The HCSR501 is a passive infrared sensor used for motion detection
 * applications. There are 5 main pins that you will need to be 
 * familiar with:
 *
 * - 5V input
 * - Signal
 * - Gnd
 * - retriggering pin
 * - non-retriggering pin
 *
 * Helpful information
 * ===================
 *
 * There are two modes to the sensor: retriggering, and
 * non-retriggering. In retriggering mode, signal outputs high as
 * long as motion is detected. In non-retriggering mode, signal
 * will output as HIGH only every second or so that motion is
 * detected.
 *
 * Quick Stats     | Value
 * ----------------|-------
 * Vcc             | **5-16V**
 * Logical voltage | **3V3**
 * Sensing range   | **7 meters**
 *
 * External Links
 * --------------
 * 
 * [Parallax PIR datasheet](http://www.ladyada.net/media/
 * sensors/PIRSensor-V1.2.pdf)
 *
 * [Elec Freaks datasheet](http://elecfreaks.com/store/download/
 * datasheet/sensor/DYP-ME003/Specification.pdf)
 *
 * [PIR motion sensors tutorial by LadyAda.net](http://
 * www.ladyada.net/learn/sensors/pir.html)
 *
 * [Supplementary Arduino code and tutorial]
 * (http://robotic-controls.com/learn/sensors/pir-sensor-hc-sr501)
 */
class HCSR501 : public Sensor
{

	int SignalPin;
	bool Signalled;

public:

	/*! \brief HCSR501 Constructor 
	 * 
	 * Initializes private variables to unused values
	 */
	HCSR501();

	/*! \brief Create a usable HCSR501 object
	 *
	 * To properly create an object in raspboop, you must use its
	 * factory Create() method. The factory method initializes
	 * the HCSR501's Signal pin using the SetInputPin() method
	 * from Sensor.
	 *
	 * \param SIGNAL The input pin which will read the value from
	 *		  		 the sensor
	 *
	 * \return A pointer to an HCSR501 object with all pins
	 *		   initialized
	 */
	static HCSR501* Create(int SIGNAL);

	virtual void Sense();

	virtual void ReleasePins();

	/*! \brief Get the value obtained from Sense()
	 *
	 * \return A boolean value determining the 
	 * 		   signal pin's value
	 */
	bool IsSignalled() const
	{
		return Signalled;
	}

	/*! \brief HCSR501 destructor
	 */
	~HCSR501();

}; /* HCSR501 */

} /* raspboop */

#endif /* RASPBOOP_SENSORS_HCSR501_H */
