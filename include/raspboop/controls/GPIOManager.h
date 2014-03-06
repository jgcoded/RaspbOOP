#ifndef RASPBOOP_CONTROLS_GPIOMANAGER_H
#define RASPBOOP_CONTROLS_GPIOMANAGER_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

/*! \brief Manages the use of GPIO pins. **Unimplemented**
 *
 * This class is not finished. 
 */
class GPIOManager
{

	map<int, int> GPIO;

	int ReservePin(int Pin, int Mode);

public:

	GPIOManager();

	int IsPinSet(int Pin);

	~GPIOManager();

}; /* GPIOManager */

} /* raspboop */

#endif /* RASPBOOP_CONTROLS_GPIOMANAGER_H */
