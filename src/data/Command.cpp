#include "raspboop/data/Command.h"

namespace raspboop
{

Command::Command() 
{
    data.commandId = -1;
    data.componentId = -1;
}

Command::Command(const Command& orig)
{
}

void Command::SetCommandParameters(vector<float> commandParameters)
{
    data.commandParameters = commandParameters;
}

vector<float> Command::GetCommandParameters() const 
{
    return data.commandParameters;
}

void Command::SetCommandId(int commandId)
{
    data.commandId = commandId;
}

int Command::GetCommandId() const 
{
    return data.commandId;
}

void Command::SetComponentId(int componentId)
{
    data.componentId = componentId;
}

int Command::GetComponentId() const 
{
    return data.componentId;
}

Command::~Command() {
}

} /* raspboop */
