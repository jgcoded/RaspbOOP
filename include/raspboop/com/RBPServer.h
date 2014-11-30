#ifndef RASPBOOP_COM_RBPSERVER_H
#define RASPBOOP_COM_RBPSERVER_H

#include "raspboop/Raspboop.h"

#include <functional>
#include <array>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::udp;

namespace raspboop
{

class RBPServer
{

public:

    typedef std::function<void(const Command*, RBPServer*)> ServerCallback;

    RBPServer(int port = 9034);

    void AddCallback(ServerCallback callback);

    void Start();

    void SendData(Serializable* data);

    void Stop();

    ~RBPServer();

private:

    void StartReceive();

    void HandleReceive();

    vector<ServerCallback> mCallbacks;

    bool mServerRunning;
    bool mStopServer;

    boost::asio::io_service mIOService;
    udp::socket mSocket;
    udp::endpoint mRemoteEndpoint;
    Command* mCommand;

};

} /* raspboop */

#endif	/* RASPBOOP_COM_RBPSERVER_H */
