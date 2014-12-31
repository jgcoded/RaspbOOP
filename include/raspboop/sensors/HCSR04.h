#ifndef RASPBOOP_SENSORS_HCSR04_H
#define RASPBOOP_SENSORS_HCSR04_H

#include "raspboop/abstracts/Sensor.h"

namespace rbp
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

    int mEchoPin;
    int mTriggerPin;
    float mEchoStart;
    float mEchoEnd;
    float mDistance;

    enum { SENSE=0, };

    unsigned char mComponentId;
    std::map<std::string, unsigned char> mCommands;

public:

    /*! \brief HCSR04 Constructor
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
    float GetDistance() const { return mDistance; }

    /*! \brief Create a usable HCSR04 object
     *
     * Initializes the HCSR04's pins using the SetInputPin() and
     * SetOutputPin() methods inherited from Sensor.
     *
     * \param echo The input pin designated to read the sensors ECHO
     * 		  output
     * \param trig The output pin that initiates sensing
     */
    HCSR04(int echo, int trig);

    virtual void AcceptCommand(const Command& command);

    virtual std::map<std::string, unsigned char> GetCommands() const;

    virtual const unsigned char GetComponentId() const;

    virtual void SetComponentId(unsigned char id);

    virtual std::vector<unsigned char> Serialize();

    /*! \brief HCSR04 Destructor
     */
    ~HCSR04();

};

} /* rbp */

#endif /* RASPBOOP_SENSORS_HCSR04_H */
