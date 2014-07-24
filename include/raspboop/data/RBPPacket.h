#ifndef RASPBOOP_DATA_RBPPACKET_H
#define	RASPBOOP_DATA_RBPPACKET_H

#include "raspboop/Raspboop.h"

namespace raspboop
{
    
struct RBPPacketData {
    uint8_t transactionID;
    uint8_t packetLength;
    uint8_t packetType;
    uint8_t checksum;
    unsigned char* data;
};

class RBPPacket {

public:
    
    RBPPacket();
    
    ~RBPPacket();
    
private:
    
    void Packint32(unsigned char* buffer, unsigned long i);
    
    int32_t Unpackint32(unsigned char* buffer);
    
    uint64_t Pack754(long double f, unsigned bits, unsigned expbits);
    
    long double Unpack754(uint64_t i, unsigned bits, unsigned expbits);
    
    RBPPacketData data;
};

} /* raspboop */

#endif	/* RASPBOOP_DATA_RBPPACKET_H */
