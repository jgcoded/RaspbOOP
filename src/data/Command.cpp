#include "raspboop/data/Command.h"

using std::vector;

namespace rbp
{

Command::Command() : mCommandId(0),
                     mComponentId(0),
                     mBodyLength(-1),
                     mCommandParameters(),
                     mIsConnectPacket(false)
{
}

Command::Command(unsigned char componentId, unsigned char commandId) :
                 mCommandId(commandId),
                 mComponentId(componentId),
                 mBodyLength(2),
                 mCommandParameters()
{
}

Command::Command(unsigned char componentId, unsigned char commandId,
                    std::vector<float> commandParameters) :
                 mCommandId(commandId),
                 mComponentId(componentId),
                 mIsConnectPacket(false)
{
    SetParameters(commandParameters);
}

bool Command::DecodeDataToCommand()
{
    mCommandParameters.clear();

    mBodyLength = mBuffer[1];
    mComponentId = mBuffer[2];
    mCommandId = mBuffer[3];

    // The first two bytes are command and component ids
    if(mBodyLength != 2 && (mBodyLength - 2) % PARAMETER_LENGTH == 0)
    {
        Buffer::const_iterator it = mBuffer.begin() + HEADER_LENGTH + 2;

        for( ; it != mBuffer.end(); it += PARAMETER_LENGTH)
        {
            float param = 0.0f;
            std::memcpy(&param, it, PARAMETER_LENGTH);
            mCommandParameters.push_back(param);
        }
        return true;
    }

    return false;
}

Command::Buffer Command::EncodeCommandToData()
{
    Buffer data;

    data[0] = START_OF_COMMAND;
    data[1] = mBodyLength;
    data[2] = mComponentId;
    data[3] = mCommandId;

    size_t i = 4;
    unsigned char* pData = data.data();
    std::vector<float>::const_iterator it = it = mCommandParameters.begin();
    for( ; it != mCommandParameters.end(); it++)
    {
        std::memcpy(pData + i, &(*it), PARAMETER_LENGTH);
        i += PARAMETER_LENGTH;
    }

    return data;
}

bool Command::IsValid()
{
    Buffer::const_iterator it = mBuffer.begin();

    if(*it == START_OF_COMMAND)
    {
        it++;
        unsigned char bodyLength = *it;

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
    mBodyLength = COMMAND_ID_LENGTH + COMMAND_ID_LENGTH +
                        mCommandParameters.size() * PARAMETER_LENGTH;
}

vector<float> Command::GetParameters() const
{
    return mCommandParameters;
}

void Command::SetCommandId(unsigned char commandId)
{
    mCommandId = commandId;
}

int Command::GetCommandId() const
{
    return mCommandId;
}

void Command::SetComponentId(unsigned char componentId)
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
