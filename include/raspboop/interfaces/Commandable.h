#ifndef RASPBOOP_INTERFACES_COMMANDABLE_H
#define	RASPBOOP_INTERFACES_COMMANDABLE_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

class Command;
    
class Commandable {

public:
    
    Commandable();
    
    virtual void AcceptCommand(const Command& data)=0;

    virtual ~Commandable()=0;
    
private:

};

} /* raspboop */

#endif	/* RASPBOOP_INTERFACES_COMMANDABLE_H */
