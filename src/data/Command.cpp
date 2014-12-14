#include "raspboop/data/Command.h"
#include <iostream>
using std::vector;

namespace rbp
{

Command::Command() : mCommandId(0),
                     mComponentId(0),
                     mCommandParameters(),
                     mBodyLength(-1),
                     mIsConnectPacket(false)
{
}

Command::Command(int8_t componentId, int8_t commandId,
                    std::vector<float> commandParameters) :
                 mCommandId(commandId),
                 mComponentId(componentId),
                 mCommandParameters(commandParameters),
                 mBodyLength(-1),
                 mIsConnectPacket(false)
{
}

bool Command::DecodeDataToCommand()
{
    mCommandParameters.clear();
    mComponentId = 0;
    mCommandId = 0;
    mBodyLength = -1;

    Buffer::const_iterator it = mBuffer.begin() + 1;

    std::memcpy(&mBodyLength, it, sizeof(int));
    it += sizeof(int);

    std::memcpy(&mComponentId, it, COMPONENT_ID_LENGTH);
    it += COMPONENT_ID_LENGTH;

    std::memcpy(&mCommandId, it, COMMAND_ID_LENGTH);
    it += COMMAND_ID_LENGTH;

    // The first two bytes are command and component ids
    if((mBodyLength - 2) % PARAMETER_LENGTH == 0)
    {
        for( ; it != mBuffer.end(); it += PARAMETER_LENGTH)
        {
            float param = 0.0f;
            std::memcpy(&param, it, PARAMETER_LENGTH);
            mCommandParameters.push_back(param);
        }
    } else {
        return false;
    }

    return true;
}

bool Command::IsValid()
{
    Buffer::const_iterator it = mBuffer.begin();

    if(*it == START_OF_COMMAND)
    {
       it++;
       int bodyLength = 0;
       std::memcpy(&bodyLength, it, sizeof(int));

       if(bodyLength > MAX_BODY_LENGTH)
           return false;

       return true;
    } else if(*it == START_OF_CONNECT) {
        mIsConnectPacket = true;
        return true;
    }

    return false;
}

Command::Buffer& Command::GetData()
{
    return mBuffer;
}

const Command::Buffer& Command::GetData() const
{
    return mBuffer;
}

bool Command::IsConnectionRequest() const
{
    return mIsConnectPacket;
}

void Command::ClearData()
{
    mCommandId = -1;
    mComponentId = -1;
    mBodyLength = -1;
    mIsConnectPacket = false;
    mCommandParameters.clear();
    mBuffer.fill(0);
}

void Command::SetParameters(vector<float> commandParameters)
{
    mCommandParameters = commandParameters;
}

vector<float> Command::GetParameters() const
{
    return mCommandParameters;
}

void Command::SetCommandId(int8_t commandId)
{
    mCommandId = commandId;
}

int Command::GetCommandId() const
{
    return mCommandId;
}

void Command::SetComponentId(int8_t componentId)
{
    mComponentId = componentId;
}

int Command::GetComponentId() const
{
    return mComponentId;
}

Command::~Command()
{
}

} /* rbp */
