#ifndef RASPBOOP_COM_SERVER_H
#define RASPBOOP_COM_SERVER_H

#include "raspboop/interfaces/Serializable.h"
#include "raspboop/data/Command.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <array>
#include <memory>
#include <functional>

using boost::asio::ip::udp;

namespace rbp
{

/*! \brief Server class used to receive Commands
 *
 * The Server class uses UDP Sockets to exchange information
 * as encoded and decoded by the Command class and the
 * Raspboop Transmission Protocol.
 *
 * The Server class also provides automatic discovery
 * functionality through a Multicast sockets. Invoke
 * EnableAutodiscovery() to start Multicasting.
 */
class Server
{

public:

    /*! \brief A convenience class used to quickly send
     *         a response code.
     */
    class ServerQuickResponseCode : public Serializable
    {
    public:
        ServerQuickResponseCode(unsigned char responseCode)
        {
            mResponseCode = responseCode;
        }

        virtual std::vector<unsigned char> Serialize()
        {
            return std::vector<unsigned char>({ mResponseCode });
        }

        unsigned char mResponseCode;
    };

    typedef std::function<void(const Command*, Server*)> ServerCallback;

    /*! \brief Instantiates a Server with a specified port
     *
     * \param port The port to bind to. Default is 9034
     */
    Server(int port = 9034);

    /*! \brief Add a callback which will be invokes when a new,
     *         valid Command is received.
     *
     * \param callback The callback to add
     */
    void AddCallback(ServerCallback callback);

    /*! \brief Begins multicasting the Server's IP and port
     *
     * \param interface The IP of the machine on which the server is running
     * \param group     The IP of the multicast group. Default is 239.255.101.33
     * \param port      The port of the multicast group. Default is 30001
     */
    void EnableAutodiscovery(std::string interface,
                             std::string group = "239.255.101.33",
                             int port = 30001);

    /*! \brief Starts receiving data and begins multicasting
     *         if enabled
     */
    void Start();

    /*! \brief Sends a Serializable to the most recent
     *         client
     *
     * \param data The Serializable to send
     */
    void SendData(Serializable* data);

    /*! \brief Stops receiving data and stops multicasting
     *         if enabled
     */
    void Stop();

    ~Server();

private:

    void StartReceive();

    void HandleReceive();

    void HandleMulticastSend(const boost::system::error_code& error, std::string data);

    std::vector<ServerCallback> mCallbacks;

    bool mServerRunning;
    bool mStopServer;

    int mPort;
    boost::asio::io_service mIOService;
    udp::socket mSocket;
    udp::endpoint mRemoteEndpoint;
    std::auto_ptr<udp::socket> mMulticastSocket;
    udp::endpoint mMulticastEndpoint;
    boost::asio::deadline_timer mTimer;
    boost::asio::ip::address mMulticastGroup;
    std::auto_ptr<Command> mCommand;

};

} /* rbp */

#endif	/* RASPBOOP_COM_SERVER_H */
