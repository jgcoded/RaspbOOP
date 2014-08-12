#ifndef RASPBOOP_DATA_RBPPACKET_H
#define	RASPBOOP_DATA_RBPPACKET_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

class RBPPacket {

public:
    
    RBPPacket();
    
    static Command* DecodeDataToCommand(unsigned char* data);
    
    static void Packint8(unsigned char* buffer, int8_t i);
    
    static int8_t Unpackint8(unsigned char* buffer);
    
    static void Packint32(unsigned char* buffer, int32_t i);
    
    static int32_t Unpackint32(unsigned char* buffer);
    
    static uint64_t Pack754(long double f, unsigned bits, unsigned expbits);
    
    static long double Unpack754(uint64_t i, unsigned bits, unsigned expbits);
    
    ~RBPPacket();
        
private:
    
};

} /* raspboop */

#endif	/* RASPBOOP_DATA_RBPPACKET_H */
