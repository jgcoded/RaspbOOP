#ifndef RASPBOOP_COM_SERVER_H
#define RASPBOOP_COM_SERVER_H

#include "raspboop/Raspboop.h"

#include <functional>
#include <array>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

using boost::asio::ip::udp;

namespace rbp
{

class Server
{

public:

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

    Server(int port =  9034);

    void AddCallback(ServerCallback callback);

    void EnableAutodiscovery(std::string interface, std::string group = "239.255.101.32", int port = 30001);

    void Start();

    void SendData(Serializable* data);

    void Stop();

    ~Server();

private:

    void StartReceive();

    void HandleReceive();

    void HandleMulticastSend(const boost::system::error_code& error, std::string data);

    std::vector<ServerCallback> mCallbacks;

    bool mServerRunning;
    bool mStopServer;

    boost::asio::io_service mIOService;
    udp::socket mSocket;
    udp::endpoint mRemoteEndpoint;
    std::auto_ptr<udp::socket> mMulticastSocket;
    udp::endpoint mMulticastEndpoint;
    boost::asio::deadline_timer mTimer;

    std::auto_ptr<Command> mCommand;

};

} /* rbp */

#endif	/* RASPBOOP_COM_SERVER_H */
