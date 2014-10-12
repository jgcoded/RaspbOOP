#include "raspboop/data/Command.h"

using std::vector;

namespace rbp
{

Command::Command() : mCommandId(-1),
                     mComponentId(-1),
                     mCommandParameters()
{
}

Command::Command(int8_t componentId, int8_t commandId,
                    std::vector<float> commandParameters) :
                 mCommandId(commandId),
                 mComponentId(componentId),
                 mCommandParameters(commandParameters)
{
}

Command Command::DecodeDataToCommand(unsigned char* data)
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
    commandId = commandId;
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
