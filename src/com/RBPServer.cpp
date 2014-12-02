#include "raspboop/com/RBPServer.h"
#include <iostream>
namespace raspboop
{

RBPServer::RBPServer(int port) :
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

void RBPServer::AddCallback(ServerCallback callback)
{
    if(callback)
        mCallbacks.push_back(callback);
}

void RBPServer::EnableAutodiscovery(std::string interface, std::string group, int port)
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
                boost::bind(&RBPServer::HandleMulticastSend,
                this,
                boost::asio::placeholders::error,
                interface));
}

void RBPServer::HandleMulticastSend(const boost::system::error_code& error, std::string data)
{
    if(!error)
    {
        mTimer.expires_from_now(boost::posix_time::seconds(1));
        mTimer.async_wait([this, data] (const boost::system::error_code& ec) {

            if(!ec)
            {
                mMulticastSocket->async_send_to(
                            boost::asio::buffer(data), mMulticastEndpoint,
                            boost::bind(&RBPServer::HandleMulticastSend, this,
                            boost::asio::placeholders::error,
                            data));
            }

        });


    }

}

void RBPServer::Start()
{
    if(mServerRunning)
        return;

    mServerRunning = true;
    mStopServer = false;

    StartReceive();

    mIOService.run();
}

void RBPServer::StartReceive()
{
    mSocket.async_receive_from(
        boost::asio::buffer(mCommand->GetData()),
        mRemoteEndpoint,
        [this] (const boost::system::error_code& error, std::size_t) {

            if(!error)
                HandleReceive();
    });
}

void RBPServer::HandleReceive()
{
    if(mCommand->IsValid())
        mCommand->DecodeDataToCommand();
    else
        mCommand->ClearData();

    for(auto& callback : mCallbacks)
        callback(mCommand.get(), this);

    if(mStopServer)
        mServerRunning = false;
    else
        StartReceive();
}

void RBPServer::SendData(Serializable* data)
{
    mSocket.async_send_to(
        boost::asio::buffer(data->Serialize()),
        mRemoteEndpoint,
        [this, data] (const boost::system::error_code&, std::size_t)
        {
            /* Should try to resend */ ;
        });
}

void RBPServer::Stop()
{
    if(mServerRunning)
    {
        mStopServer = true;
        mIOService.stop();
        mSocket.shutdown(udp::socket::shutdown_both);
        mSocket.close();
    }
}

RBPServer::~RBPServer()
{
    Stop();
}

} /* raspboop */
