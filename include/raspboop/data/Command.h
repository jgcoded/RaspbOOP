#ifndef RASPBOOP_DATA_COMMAND_H
#define	RASPBOOP_DATA_COMMAND_H

#include <cstddef>
#include <vector>
#include <array>
#include <cstring>

namespace rbp
{

class Command
{

#define     HEADER_LENGTH        2*sizeof(unsigned char)
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

    Command(unsigned char componentId, unsigned char commandId);

    Command(unsigned char componentId, unsigned char commandId,
                                std::vector<float> commandParameters);

    bool DecodeDataToCommand();

    Buffer EncodeCommandToData();

    bool IsValid();

    Buffer& GetData();

    const Buffer& GetData() const;

    bool IsConnectionRequest() const;

    void ClearData();

    void SetParameters(std::vector<float> commandParameters);

    std::vector<float> GetParameters() const;

    void SetCommandId(unsigned char commandId);

    int GetCommandId() const;

    void SetComponentId(unsigned char componentId);

    int GetComponentId() const;

    float GetParameterAtIndex(size_t i) const;

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
