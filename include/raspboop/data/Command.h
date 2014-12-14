#ifndef RASPBOOP_DATA_COMMAND_H
#define	RASPBOOP_DATA_COMMAND_H

#include <vector>
#include <stdint.h>
#include <cstring>
#include <array>

namespace rbp
{

class Command {

#define     HEADER_LENGTH        sizeof(unsigned char) + sizeof(int)
#define     MAX_BODY_LENGTH      130
#define     MAX_COMMAND_LENGTH   (HEADER_LENGTH + MAX_BODY_LENGTH)
#define     START_OF_COMMAND     0x55
#define     START_OF_CONNECT     0x56
#define     COMPONENT_ID_LENGTH  sizeof(unsigned char)
#define     COMMAND_ID_LENGTH    sizeof(unsigned char)
#define     PARAMETER_LENGTH     sizeof(float)

public:

    typedef std::array<unsigned char, MAX_COMMAND_LENGTH> Buffer;

    Command();

    Command(int8_t componentId, int8_t commandId,
                                std::vector<float> commandParameters);

    bool DecodeDataToCommand();

    bool IsValid();

    Buffer& GetData();

    const Buffer& GetData() const;

    bool IsConnectionRequest() const;

    void ClearData();

    void SetParameters(std::vector<float> commandParameters);

    std::vector<float> GetParameters() const;

    void SetCommandId(int8_t commandId);

    int GetCommandId() const;

    void SetComponentId(int8_t componentId);

    int GetComponentId() const;

    virtual ~Command();

private:

    unsigned char mComponentId;
    unsigned char mCommandId;
    bool mIsConnectPacket;
    std::vector<float> mCommandParameters;
    Buffer mBuffer;
    int mBodyLength;

};

} /* rbp */

#endif	/* RASPBOOP_DATA_COMMAND_H */
