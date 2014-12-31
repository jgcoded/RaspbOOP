#ifndef RASPBOOP_ABSTRACTS_SENSOR_H
#define RASPBOOP_ABSTRACTS_SENSOR_H

#include "raspboop/abstracts/GPIOConsumer.h"

namespace rbp
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
    void SetOutputPin(int pin);

    /*! \brief Set an input pin for the sensor
     *
     * Consumes a pin to be designated as an input. This is usually
     * the pin that will be receiving data from the sensor.
     *
     * \param Pin The pin to designate as in input
     */
    void SetInputPin(int pin);

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

} /* rbp */

#endif /* RASPBOOP_INTERFACES_SENSOR_H */
