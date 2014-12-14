#ifndef RASPBOOP_INTERFACES_SERIALIZABLE_H
#define	RASPBOOP_INTERFACES_SERIALIZABLE_H

#include "raspboop/Raspboop.h"

namespace rbp
{

class Serializable {

public:

    virtual std::vector<unsigned char> Serialize()=0;

private:

};

} /* rbp */

#endif	/* RASPBOOP_INTERFACES_SERIALIZABLE_H */
