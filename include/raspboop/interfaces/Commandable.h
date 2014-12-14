#ifndef RASPBOOP_INTERFACES_COMMANDABLE_H
#define	RASPBOOP_INTERFACES_COMMANDABLE_H

#include "raspboop/Raspboop.h"

namespace rbp
{

class Command;

class Commandable {

public:

    virtual void AcceptCommand(const Command& data)=0;

private:

};

} /* rbp */

#endif	/* RASPBOOP_INTERFACES_COMMANDABLE_H */
