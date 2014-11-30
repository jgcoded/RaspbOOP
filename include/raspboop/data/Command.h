#ifndef RASPBOOP_DATA_COMMAND_H
#define	RASPBOOP_DATA_COMMAND_H

#include "raspboop/Raspboop.h"

#include <array>

namespace raspboop
{

class Command {

#define     HEADER_LENGTH        sizeof(unsigned char) + sizeof(int)
#define     MAX_BODY_LENGTH      130
#define     MAX_COMMAND_LENGTH   (HEADER_LENGTH + MAX_BODY_LENGTH)
#define     START_OF_COMMAND     0x55
#define     COMPONENT_ID_LENGTH  sizeof(unsigned char)
#define     COMMAND_ID_LENGTH    sizeof(unsigned char)
#define     PARAMETER_LENGTH     sizeof(float)

public:

    typedef std::array<unsigned char, MAX_COMMAND_LENGTH> Buffer;

    Command();

    Command(int8_t componentId, int8_t commandId,
                                vector<float> commandParameters);

    bool DecodeDataToCommand();

    bool IsValid() const;

    Buffer& GetData();

    const Buffer& GetData() const;

    void ClearData();

    void SetCommandParameters(vector<float> commandParameters);

    vector<float> GetCommandParameters() const;

    void SetCommandId(int8_t commandId);

    int GetCommandId() const;

    void SetComponentId(int8_t componentId);

    int GetComponentId() const;

    virtual ~Command();

private:

    unsigned char mComponentId;
    unsigned char mCommandId;
    vector<float> mCommandParameters;
    Buffer mBuffer;
    int mBodyLength;

};

} /* raspboop */

#endif	/* RASPBOOP_DATA_COMMAND_H */
