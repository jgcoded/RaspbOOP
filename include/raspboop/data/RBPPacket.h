#ifndef RASPBOOP_DATA_RBPPACKET_H
#define	RASPBOOP_DATA_RBPPACKET_H

#include "raspboop/Raspboop.h"
#include <cstring>

namespace raspboop
{

/** \brief Advances the dest pointer by size */
static void* rbpbufset(unsigned char*& dest, const void* source, size_t size)
{
    void* v = std::memcpy(dest, source, size);
    dest += size;
    return v;
}

/** \brief Advances the source pointer by size */
static void* rbpbufget(void* dest, unsigned char* source, size_t size)
{
    void* v = std::memcpy(dest, source, size);
    source += size;
    return v;
}

class RBPPacket {

public:

    RBPPacket();

    static Command DecodeDataToCommand(unsigned char* data);

    ~RBPPacket();

private:

};

} /* raspboop */

#endif	/* RASPBOOP_DATA_RBPPACKET_H */
