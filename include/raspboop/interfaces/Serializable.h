#ifndef RASPBOOP_INTERFACES_SERIALIZABLE_H
#define	RASPBOOP_INTERFACES_SERIALIZABLE_H

#include <vector>

namespace rbp
{

/*! \brief Interface for objects that can be serialized
 *
 */
class Serializable {

public:

    /*! \brief Returns an array representation of an object
     *
     * \return The Buffer of data
     */
    virtual std::vector<unsigned char> Serialize()=0;

private:

};

} /* rbp */

#endif	/* RASPBOOP_INTERFACES_SERIALIZABLE_H */
