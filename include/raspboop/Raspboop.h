#ifndef RASPBOOP_H
#define RASPBOOP_H

/* System includes */
#include <stdio.h>
#include <map>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#include <errno.h>

using std::map;

/* Dependency includes */
#include <wiringPi.h>
#include <softPwm.h>

/* Raspboop source */
#include "raspboop/essentials/Core.h"
#include "raspboop/abstracts/GPIOConsumer.h"
#include "raspboop/abstracts/Sensor.h"
#include "raspboop/boards/L298N.h"
#include "raspboop/sensors/HCSR04.h"
#include "raspboop/sensors/HCSR501.h"
#include "raspboop/controls/GPIOManager.h"

#endif /* RASPBOOP_H */
