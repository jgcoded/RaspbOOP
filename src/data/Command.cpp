#include "raspboop/data/Command.h"

namespace raspboop
{

Command::Command() 
{
    commandId = -1;
    componentId = -1;
}

Command* Command::CreateCommand(int8_t componentId, int8_t commandId, 
                                           vector<float> commandParameters)
{
    Command* C;
    
    C = (Command*)malloc(sizeof(Command));
    
    if(C == NULL)
        return NULL;
    
    new (C) Command;
    
    C->componentId = componentId;
    C->commandId = commandId;
    C->commandParameters = commandParameters;
    
    return C;
}

void Command::SetCommandParameters(vector<float> commandParameters)
{
    commandParameters = commandParameters;
}

vector<float> Command::GetCommandParameters() const 
{
    return commandParameters;
}

void Command::SetCommandId(int8_t commandId)
{
    commandId = commandId;
}

int Command::GetCommandId() const 
{
    return commandId;
}

void Command::SetComponentId(int8_t componentId)
{
    componentId = componentId;
}

int Command::GetComponentId() const 
{
    return componentId;
}

Command::~Command() {
}

} /* raspboop */
