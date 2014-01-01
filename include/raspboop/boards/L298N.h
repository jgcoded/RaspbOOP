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

#ifndef RASPBOOP_BOARDS_L298N_BOARD_H
#define RASPBOOP_BOARDS_L298N_BOARD_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

/*! \brief L298N Motor controller
 *
 * This class is meant to support the L298N motor controller
 * board. In most cases, the Enable A, B, and 5V pins are
 * connected by default through jumpers on most model #236
 * board.
 *
 * Helpful information
 * ===================
 * - This board is able to control two motors at the same time.
 * - Do not input a voltage into the 5V terminal
 * 		- If the voltage in the 12V terminal is greater than 12V,
 *		  then you can use the 5V terminal as a power source.
 *
 *     Quick Stats           | Value
 *---------------------------|-----------
 * Maximum input voltage     | **46V**
 * Continuous output current | **2 Amps**
 * Maximum output current    | **3 Amps**
 * Logical voltage           | **5V**
 * Max Logical current       | **36 mA**
 * Maximum output            | **25 W**
 *
 * External links
 * --------------
 * [Datasheet](http://www.st.com/st-web-ui/static/active/en/
 * resource/technical/document/datasheet/CD00000240.pdf)
 *
 * [Blog post:](http://zapterra.com/systems/articles/electronics/
 * l298-motor-driver-tutorial-arduino/)
 * Very informative and detailed blog post. Recommended if you need
 * an introduction to the chip.
 */
class L298N : public GPIOConsumer
{

	int Pins[4];

public:

	L298N();

	/*! \brief Creates a pointer to an L298N object
	 *
	 * To properly create an object in raspboop, you must use its
	 * factory Create() method. The factory method initializes
	 * the L298N's pins using the ConsumePin() method.
	 *
	 * \param IN1 The board's IN1 pin
	 * \param IN2 The board's IN2 pin
	 * \param IN3 The board's IN3 pin
	 * \param IN4 The board's IN4 pin
	 * 
	 * \return A pointer to an L298N object with all pins
	 * 		   ready to operate.
	 */
	static L298N* Create(int IN1, int IN2, int IN3, int IN4);

	/*! \brief Sets the input pins to software PWM mode
	 *
	 * Uses wiringPi's [software PWM library](http://wiringpi.com/
	 * reference/software-pwm-library/)
	 * to set the pins provided in the Create() factory method to
	 * a software PWM mode
	 *
	 * **Note:** Software PWM operates on seperate threads, and
	 * 			 each thread consumes about 0.5% CPU, according
	 *			 to the wiringPi reference.
	 */
	void UseSoftPWM();

	/*! \brief Sets a pin's software PWM value
	 *
	 * This method uses wiringPi's 
	 * [software PWM library](http://wiringpi.com/reference/
	 * software-pwm-library/) to set the software
	 * PWM on the pin to a value. You must first call the
	 * UseSoftPwm() method before using this method.
	 *
	 * \param IN Value of 1 ~ 4 that represents the physical
	 *			 IN pin on the board
	 * \param Value A value from 0 to 100
	 */
	void SetPWMValue(int IN, int Value);

	/*! \brief Set a pin's value to either HIGH or LOW
	 *
	 * This is equivalent to calling wiringPi's digitalWrite()
	 * method
	 *
	 * \param IN Value of 1 ~ 4 that represents the physical
	 *			 IN pin on the board
	 * \param Value A value of HIGH(1) or LOW(0)
	 */
	void SetPinValue(int IN, int Value);

	virtual void ReleasePins();

	~L298N();

}; /* L298N */

} /* raspboop */

#endif /* RASPBOOP_BOARDS_L298N_H */
