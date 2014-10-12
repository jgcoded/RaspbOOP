#ifndef RASPBOOP_DATA_COMMAND_H
#define	RASPBOOP_DATA_COMMAND_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

class Command {

public:

    Command();

    Command(int8_t componentId, int8_t commandId,
                                vector<float> commandParameters);

    void SetCommandParameters(vector<float> commandParameters);

    vector<float> GetCommandParameters() const;

    void SetCommandId(int8_t commandId);

    int GetCommandId() const;

    void SetComponentId(int8_t componentId);

    int GetComponentId() const;

    virtual ~Command();

private:

    int8_t mComponentId;
    int8_t mCommandId;
    vector<float> mCommandParameters;

};

} /* raspboop */

#endif	/* RASPBOOP_DATA_COMMAND_H */
