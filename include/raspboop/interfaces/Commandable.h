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
     *         if the command exists within GetCommands()
     *
     * \param data The command to accept
     */
    virtual void AcceptCommand(const Command& data)=0;

    /*! \brief Get a map of a human readable string and
     *         its respective command ID
     *
     * \return A map of command names and respective IDs
     */
    virtual std::map<std::string, unsigned char> GetCommands() const=0;

    /*! \brief Get the physical component's ID
     *
     * \return The physical component's ID
     */
    virtual const unsigned char GetComponentId() const=0;

    /*! \brief Set the physical component's ID
     *
     * \param id The ID to use
     */
    virtual void SetComponentId(unsigned char id)=0;

protected:

};

} /* rbp */

#endif	/* RASPBOOP_INTERFACES_COMMANDABLE_H */
