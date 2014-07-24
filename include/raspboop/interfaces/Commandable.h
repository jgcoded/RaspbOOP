#ifndef RASPBOOP_INTERFACES_COMMANDABLE_H
#define	RASPBOOP_INTERFACES_COMMANDABLE_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

class Commandable {

public:
    
    Commandable();
    
    virtual void AcceptCommand(const struct CommandData* data)=0;
    
    virtual struct RBPPacketData* ToRBPPacketData();
    
    virtual ~Commandable()=0;
    
private:

};

} /* raspboop */

#endif	/* RASPBOOP_INTERFACES_COMMANDABLE_H */
