#include "raspboop/data/RBPPacket.h"
#include <iostream>
namespace raspboop
{

RBPPacket::RBPPacket()
{

}

Command RBPPacket::DecodeDataToCommand(unsigned char* data)
{
    int8_t componentId;
    int8_t commandId;
    float param1;
    float param2;
    vector<float> cmdParams;

    cmdParams.reserve(4);

    std::memcpy(&componentId, data, sizeof(int8_t));
    data += sizeof(int8_t);

    std::memcpy(&commandId, data, sizeof(int8_t));
    data += sizeof(int8_t);

    std::memcpy(&param1, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&param2, data, sizeof(float));
    data += sizeof(float);

    cmdParams.push_back(param1);
    cmdParams.push_back(param2);
    return Command(componentId, commandId, cmdParams);
}

RBPPacket::~RBPPacket()
{
}

} /* raspboop */
