#ifndef RASPBOOP_DATA_COMMAND_H
#define	RASPBOOP_DATA_COMMAND_H

#include "raspboop/Raspboop.h"
#include <vector>
#include <stdint.h>

namespace rbp
{

class Command {

public:

    Command();

    Command(int8_t componentId, int8_t commandId,
                                std::vector<float> commandParameters);

    static Command DecodeDataToCommand(unsigned char* data);

    void SetParameters(std::vector<float> commandParameters);

    std::vector<float> GetParameters() const;

    void SetCommandId(int8_t commandId);

    int GetCommandId() const;

    void SetComponentId(int8_t componentId);

    int GetComponentId() const;

    virtual ~Command();

private:

    int8_t mComponentId;
    int8_t mCommandId;
    std::vector<float> mCommandParameters;

};

} /* rbp */

#endif	/* RASPBOOP_DATA_COMMAND_H */
