#include "raspboop/data/RBPPacket.h"

namespace raspboop
{
    
#define pack754_32(f) (Pack754((f), 32, 8))
#define pack754_64(f) (Pack754((f), 64, 11))
#define unpack754_32(i) (Unpack754((i), 32, 8))
#define unpack754_64(i) (Unpack754((i), 64, 11))

RBPPacket::RBPPacket() 
{

}

Command* RBPPacket::DecodeDataToCommand(unsigned char* data)
{
    int8_t componentId;
    int8_t commandId;
    vector<float> cmdParams;
    int index = 0;
    
    cmdParams.reserve(4);
    
    componentId = Unpackint8(data);
    index++;
    
    commandId = Unpackint8(data + index);
    index++;
    
    while(data[index] != '\0')
    {
        int32_t fparam = Unpackint32(data + index);
        cmdParams.push_back(unpack754_32(fparam));
        index += 4;
    }
    
    return Command::CreateCommand(componentId, commandId, cmdParams);
}

 void RBPPacket::Packint8(unsigned char* buffer, int8_t i)
 {
     *buffer++ = (i >> 0) & 0xff;
 }
    
 int8_t RBPPacket::Unpackint8(unsigned char* buffer)
 {
     return *buffer++;
 }

void RBPPacket::Packint32(unsigned char* buffer, int32_t i)
{
    *buffer++ = i >> 24;
    *buffer++ = i >> 16;
    *buffer++ = i >> 8;
    *buffer++ = i;
}

int32_t RBPPacket::Unpackint32(unsigned char* buffer)
{
    return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
}

uint64_t RBPPacket::Pack754(long double f, unsigned bits, unsigned expbits)
{
    long double fnorm;
    int shift;
    long long sign, exp, significand;
    unsigned significandbits = bits - expbits - 1; // -1 for sign bit

    if (f == 0.0) return 0; // get this special case out of the way

    // check sign and begin normalization
    if (f < 0) { sign = 1; fnorm = -f; }
    else { sign = 0; fnorm = f; }

    // get the normalized form of f and track the exponent
    shift = 0;
    while(fnorm >= 2.0) { fnorm /= 2.0; shift++; }
    while(fnorm < 1.0) { fnorm *= 2.0; shift--; }
    fnorm = fnorm - 1.0;

    // calculate the binary form (non-float) of the significand data
    significand = fnorm * ((1LL<<significandbits) + 0.5f);

    // get the biased exponent
    exp = shift + ((1<<(expbits-1)) - 1); // shift + bias

    // return the final answer
    return (sign<<(bits-1)) | (exp<<(bits-expbits-1)) | significand;
}
    
long double RBPPacket::Unpack754(uint64_t i, unsigned bits, unsigned expbits)
{
    long double result;
    long long shift;
    unsigned bias;
    unsigned significandbits = bits - expbits - 1; // -1 for sign bit

    if (i == 0) return 0.0;

    // pull the significand
    result = (i&((1LL<<significandbits)-1)); // mask
    result /= (1LL<<significandbits); // convert back to float
    result += 1.0f; // add the one back on

    // deal with the exponent
    bias = (1<<(expbits-1)) - 1;
    shift = ((i>>significandbits)&((1LL<<expbits)-1)) - bias;
    while(shift > 0) { result *= 2.0; shift--; }
    while(shift < 0) { result /= 2.0; shift++; }

    // sign it
    result *= (i>>(bits-1))&1? -1.0: 1.0;

    return result;
}


RBPPacket::~RBPPacket() 
{
}

} /* raspboop */
