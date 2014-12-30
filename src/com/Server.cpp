#include "raspboop/Raspboop.h"
#include <iostream>

namespace rbp
{

Server::Server(int port) :
                         mIOService(),
                         mPort(port),
                         mSocket(mIOService, udp::endpoint(udp::v4(), port)),
                         mServerRunning(false),
                         mStopServer(false),
                         mCommand(new Command),
                         mMulticastSocket(),
                         mTimer(mIOService)
{
    mCommand->ClearData();
    mSocket.set_option(udp::socket::reuse_address(true));
}

void Server::AddCallback(ServerCallback callback)
{
    if(callback)
        mCallbacks.push_back(callback);
}

void Server::EnableAutodiscovery(std::string interface, std::string group, int port)
{
    mMulticastSocket.reset(new udp::socket(mIOService));

    mMulticastGroup = boost::asio::ip::address::from_string(group);
    boost::asio::ip::address localIp =boost::asio::ip::address::from_string(interface);
    mMulticastEndpoint = udp::endpoint(mMulticastGroup, port);

    mMulticastSocket->open(mMulticastEndpoint.protocol());


    mMulticastSocket->set_option(udp::socket::reuse_address(true));


    mMulticastSocket->bind(udp::endpoint(localIp, port));


    mMulticastSocket->set_option(boost::asio::ip::multicast::join_group(mMulticastGroup.to_v4(), localIp.to_v4()));


    mMulticastSocket->set_option(boost::asio::ip::multicast::hops(5));


    mMulticastSocket->set_option(boost::asio::ip::multicast::enable_loopback(true));


    mMulticastSocket->set_option(boost::asio::socket_base::broadcast(true));


    boost::asio::socket_base::receive_buffer_size receiveSize(100);
    mMulticastSocket->set_option(receiveSize);
    boost::asio::socket_base::send_buffer_size sendSize(100);
    mMulticastSocket->set_option(sendSize);

    std::stringstream ss;
    ss << interface << ":" << mPort << "END";
    std::string data = ss.str();
    mMulticastSocket->async_send_to(
                boost::asio::buffer(data),
                mMulticastEndpoint,
                boost::bind(&Server::HandleMulticastSend,
                this,
                boost::asio::placeholders::error,
                data));
}

void Server::HandleMulticastSend(const boost::system::error_code& error, std::string data)
{
    if(!error)
    {
        mTimer.expires_from_now(boost::posix_time::seconds(1));
        mTimer.async_wait([this, data] (const boost::system::error_code& ec) {

            if(!ec)
            {
                mMulticastSocket->async_send_to(
                            boost::asio::buffer(data), mMulticastEndpoint,
                            boost::bind(&Server::HandleMulticastSend, this,
                            boost::asio::placeholders::error,
                            data));
            }

        });
    }

}

void Server::Start()
{
    if(mServerRunning)
        return;

    mServerRunning = true;
    mStopServer = false;

    StartReceive();

    mIOService.run();
}

void Server::StartReceive()
{
    mSocket.async_receive_from(
        boost::asio::buffer(mCommand->GetData()),
        mRemoteEndpoint,
        [this] (const boost::system::error_code& error, std::size_t) {

            if(!error)
                HandleReceive();
    });
}

void Server::HandleReceive()
{std::cout << "here" << std::endl;
    if(mCommand->IsValid())
    {
        if(mCommand->IsConnectionRequest())
        {
            // let the client know we're good to go by echoing received data
            ServerQuickResponseCode reply(mCommand->GetData().front());
            SendData(&reply);

        } else {

            mCommand->DecodeDataToCommand();

            for(auto& callback : mCallbacks)
                callback(mCommand.get(), this);
        }

    }

    mCommand->ClearData();

    if(mStopServer)
        mServerRunning = false;
    else
        StartReceive();
}

void Server::SendData(Serializable* data)
{
    // do not access parameter data unless you protect it
    mSocket.async_send_to(
        boost::asio::buffer(data->Serialize()),
        mRemoteEndpoint,
        [this] (const boost::system::error_code&, std::size_t)
        {
                    std::cout << "Sent data to: "
                              << mRemoteEndpoint.address().to_string()
                              << " "
                              << mRemoteEndpoint.port()
                              << std::endl;
            /* Should try to resend */
        });
}

void Server::Stop()
{
    mStopServer = true;
    mIOService.stop();
    mSocket.shutdown(udp::socket::shutdown_both);
    mSocket.close();
    mMulticastSocket->set_option(boost::asio::ip::multicast::leave_group(mMulticastGroup));
    mMulticastSocket->shutdown(udp::socket::shutdown_send);
    mMulticastSocket->close();
    mMulticastSocket.reset();
}

Server::~Server()
{
    Stop();
}

} /* rbp */
