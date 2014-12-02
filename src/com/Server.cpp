#include "raspboop/Raspboop.h"

namespace rbp
{

Server::Server(int port) :
                         mIOService(),
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
    boost::asio::ip::address multicastIP =
                boost::asio::ip::address::from_string(group);

    mMulticastEndpoint = udp::endpoint(multicastIP, port);

    mMulticastSocket.reset(new udp::socket(mIOService,
                mMulticastEndpoint.protocol()));

    mMulticastSocket->set_option(udp::socket::reuse_address(true));

    mMulticastSocket->async_send_to(
                boost::asio::buffer(interface),
                mMulticastEndpoint,
                boost::bind(&Server::HandleMulticastSend,
                this,
                boost::asio::placeholders::error,
                interface));
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
{
    if(mCommand->IsValid())
    {
        mCommand->DecodeDataToCommand();


    for(auto& callback : mCallbacks)
        callback(mCommand.get(), this);

    } else {
        mCommand->ClearData();
    }

    if(mStopServer)
        mServerRunning = false;
    else
        StartReceive();
}

void Server::SendData(Serializable* data)
{
    mSocket.async_send_to(
        boost::asio::buffer(data->Serialize()),
        mRemoteEndpoint,
        [this, data] (const boost::system::error_code&, std::size_t)
        {
            /* Should try to resend */ ;
        });
}

void Server::Stop()
{
    mStopServer = true;
    mIOService.stop();
    mSocket.shutdown(udp::socket::shutdown_both);
    mSocket.close();
    mMulticastSocket->shutdown(udp::socket::shutdown_send);
    mMulticastSocket->close();
    mMulticastSocket.reset();
}

Server::~Server()
{
    Stop();
}

} /* rbp */
