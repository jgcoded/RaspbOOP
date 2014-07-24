#ifndef RASPBOOP_INTERFACES_SERIALIZABLE_H
#define	RASPBOOP_INTERFACES_SERIALIZABLE_H

namespace raspboop
{

class Serializable {
    
public:
    
    Serializable();
    
    virtual unsigned char* Serialize()=0;
    
    virtual ~Serializable()=0;
    
private:

};

} /* raspboop */

#endif	/* RASPBOOP_INTERFACES_SERIALIZABLE_H */
