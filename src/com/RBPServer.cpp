#include "raspboop/com/RBPServer.h"

namespace raspboop
{

RBPServer::RBPServer(int port) : mIOService(),
                         mSocket(mIOService, udp::endpoint(udp::v4(), port)),
                         mServerRunning(false),
                         mStopServer(false),
                         mCommand(new Command)
{
}

void RBPServer::AddCallback(ServerCallback callback)
{
    if(callback)
        mCallbacks.push_back(callback);
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
        callback(mCommand, this);

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
