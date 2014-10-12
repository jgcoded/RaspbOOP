#ifndef RASPBOOP_H
#define RASPBOOP_H

/* System includes */
#include <stdio.h>
#include <map>
#include <vector>
#include <stdint.h>
#include <pthread.h>
#include <errno.h>
#include <algorithm>

using std::vector;

/* Dependency includes */
#include <wiringPi.h>
#include <softPwm.h>

/* Raspboop source */

#include "raspboop/essentials/Types.h"
#include "raspboop/essentials/Core.h"
#include "raspboop/abstracts/GPIOConsumer.h"
#include "raspboop/abstracts/Sensor.h"
#include "raspboop/boards/L298N.h"
#include "raspboop/sensors/HCSR04.h"
#include "raspboop/sensors/HCSR501.h"
#include "raspboop/interfaces/Serializable.h"
#include "raspboop/data/Command.h"
#include "raspboop/interfaces/Commandable.h"
#include "raspboop/com/Server.h"

#endif /* RASPBOOP_H */
