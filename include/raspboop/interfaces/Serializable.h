#ifndef RASPBOOP_INTERFACES_SERIALIZABLE_H
#define	RASPBOOP_INTERFACES_SERIALIZABLE_H

#include "raspboop/Raspboop.h"

namespace rbp
{

class Serializable {

public:

    Serializable();
    
    virtual std::vector<unsigned char> Serialize()=0;
    
    virtual ~Serializable()=0;

private:

};

} /* rbp */

#endif	/* RASPBOOP_INTERFACES_SERIALIZABLE_H */
