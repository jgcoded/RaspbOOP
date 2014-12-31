#ifndef RASPBOOP_DATA_COMMAND_H
#define	RASPBOOP_DATA_COMMAND_H

#include <cstddef>
#include <vector>
#include <array>
#include <cstring>

namespace rbp
{

/*! \brief Encapsulates data into a command
 *
 * This class is responsible for the encoding and decoding
 * of data into and out of the Raspboop Transmission
 * Protocol (RTP). The RTP is formatted as follows:
 *
 * { START OF PACKET, BODY LENGTH, COMPONENT ID,
 *   COMMAND ID, PARAMETERS... }
 *
 *     Name      | Definition | Memory Usage
 *---------------|------------|----------------------
 * START OF PACKET | An arbitrary value that starts every packet   | 1 byte
 * BODY LENGTH     | The size of the remaining portion of the data | 1 byte
 * COMPONENT ID    | An ID representing a physical component       | 1 byte
 * COMMAND ID      | The ID of a Component's command               | 1 byte
 * PARAMETERS      | An array of floats                            | 8*x bytes
 *
 * * The RTP also specifies another arbitrary value that
 *   can commence a packet of data: a CONNECTION REQUEST
 *
 * Command takes care of formatting the data into
 * the RTP specification.
 */
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

    /*! \brief Creates a Command with an empty parameter list
     *
     * \param componentId The ID of the physical component
     * \param commandId   The ID of a Component's command
     */
    Command(unsigned char componentId, unsigned char commandId);

    /*! \brief Creates a Command with the specified parameter list
     *
     * \param componentId       The ID of the physical component
     * \param commandId         The ID of a Component's command
     * \param commandParameters Initial values of the command
     */
    Command(unsigned char componentId, unsigned char commandId,
                                std::vector<float> commandParameters);

    /*! \brief Decodes data and sets private members
     *
     * \return True on success, False on failure
     */
    bool DecodeDataToCommand();

    /*! \brief Encodes private members into a buffer
     *
     * \return a Buffer with data formatted to RTP
     *         specification
     */
    Buffer EncodeCommandToData();

    /*! \brief Check if the data is formatted to RTP
     *         specification
     *
     * \return True on success, False on failure
     */
    bool IsValid();

    /*! \brief Get a non-const reference to the
     *         class buffer
     *
     * \return Internal Buffer object
     */
    Buffer& GetData();

    /*! \brief Get a const reference to the
     *         class buffer
     *
     * \return Internal Buffer object
     */
    const Buffer& GetData() const;

    /*! \brief Checks if the internal Buffer object
     *         is a connection request
     *
     * \return True if the buffer object data begins with
     *         the connection request value
     */
    bool IsConnectionRequest() const;

    /*! \brief Clears the internal Buffer object data
     */
    void ClearData();

    /*! \brief Set the Command's parameter list
     *
     * \param commandParameters The parameter list
     */
    void SetParameters(std::vector<float> commandParameters);

    /*! \brief Get the Command's parameter list
     *
     * \return The parameter list
     */
    std::vector<float> GetParameters() const;

    /*! \brief Set the command id of the Command
     *
     * \param commandId The command ID
     */
    void SetCommandId(unsigned char commandId);

    /*! \brief Get the Command ID
     *
     * \return The Command ID
     */
    int GetCommandId() const;

    /*! \brief Sets the physical component's ID
     *
     * \param componentID The component's ID
     */
    void SetComponentId(unsigned char componentId);

    /*! \brief Get the physical component's ID
     *
     * \return The physical component's ID
     */
    int GetComponentId() const;

    /*! \brief Gets a parameter at the specified index
     *
     * \param i The index
     *
     * \return The parameter at index i
     */
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
