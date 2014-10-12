#ifndef RASPBOOP_BOARDS_L298N_BOARD_H
#define RASPBOOP_BOARDS_L298N_BOARD_H

#include "raspboop/Raspboop.h"

namespace rbp
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
     * \param in1 The board's IN1 pin
     * \param in2 The board's IN2 pin
     * \param in3 The board's IN3 pin
     * \param in4 The board's IN4 pin
     *
     * \return A pointer to an L298N object with all pins
     * 		   ready to operate.
     */
    static L298N* Create(int in1, int in2, int in3, int in4);

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
    void SetPWMValue(int in, int value);

    /*! \brief Set a pin's value to either HIGH or LOW
     *
     * This is equivalent to calling wiringPi's digitalWrite()
     * method
     *
     * \param IN Value of 1 ~ 4 that represents the physical
     *			 IN pin on the board
     * \param Value A value of HIGH(1) or LOW(0)
     */
    void SetPinValue(int in, int value);

    ~L298N();

}; /* L298N */

} /* rbp */

#endif /* RASPBOOP_BOARDS_L298N_H */
