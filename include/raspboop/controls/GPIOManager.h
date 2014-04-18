#ifndef RASPBOOP_CONTROLS_GPIOMANAGER_H
#define RASPBOOP_CONTROLS_GPIOMANAGER_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

/*! \brief Manages the use of GPIO pins. **Unimplemented**
 *
 * This class is not finished. 
 */
class GPIOManager : public GPIOConsumer
{

    vector<GPIOConsumer*> ConsumerList;
        
public:

    GPIOManager();

    bool IsPinSet(int Pin);

    int AddConsumer(GPIOConsumer* Consumer);

    ~GPIOManager();

}; /* GPIOManager */

} /* raspboop */

#endif /* RASPBOOP_CONTROLS_GPIOMANAGER_H */
