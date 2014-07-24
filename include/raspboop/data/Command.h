#ifndef RASPBOOP_DATA_COMMAND_H
#define	RASPBOOP_DATA_COMMAND_H

#include "raspboop/Raspboop.h"

namespace raspboop
{
    
struct CommandData
{
    int componentId;
    int commandId;
    vector<float> commandParameters;
};
    
class Command {
    
public:
    
    Command();
    
    Command(int componentId, int commandId, vector<float> commandParameters);

    Command(const Command& orig);
    
    void SetCommandParameters(vector<float> commandParameters);

    vector<float> GetCommandParameters() const;

    void SetCommandId(int commandId);

    int GetCommandId() const;

    void SetComponentId(int componentId);

    int GetComponentId() const;
    
    virtual ~Command();
    
private:

    CommandData data;
    
};

} /* raspboop */

#endif	/* RASPBOOP_DATA_COMMAND_H */
