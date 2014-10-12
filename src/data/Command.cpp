#include "raspboop/data/Command.h"

namespace raspboop
{

Command::Command() : mCommandId(-1),
                     mComponentId(-1),
                     mCommandParameters()
{
}

Command::Command(int8_t componentId, int8_t commandId,
                    vector<float> commandParameters) :
                 mCommandId(commandId),
                 mComponentId(componentId),
                 mCommandParameters(commandParameters)
{
}

void Command::SetCommandParameters(vector<float> commandParameters)
{
    mCommandParameters = commandParameters;
}

vector<float> Command::GetCommandParameters() const
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

} /* raspboop */
