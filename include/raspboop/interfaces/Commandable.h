#ifndef RASPBOOP_INTERFACES_COMMANDABLE_H
#define	RASPBOOP_INTERFACES_COMMANDABLE_H

#include "raspboop/data/Command.h"
#include <string>
#include <map>

namespace rbp
{

/*! \brief Interface for objects that can accept Commands
 *
 */
class Commandable {

public:

    /*! \brief Accepts a Command and performs an operation
     *
     */
    virtual void AcceptCommand(const Command& data)=0;

    virtual std::map<std::string, unsigned char> GetCommands()=0;

    virtual unsigned char GetComponentId()=0;

    virtual void SetComponentId(unsigned char id)=0;

protected:

};

} /* rbp */

#endif	/* RASPBOOP_INTERFACES_COMMANDABLE_H */
