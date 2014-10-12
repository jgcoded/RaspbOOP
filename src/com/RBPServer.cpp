#include "raspboop/Raspboop.h"
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <exception>
#include <stdexcept>
#include <thread>
#include <iostream>

#define RBPPORT "9034"

namespace raspboop
{

RBPServer::RBPServer() : mSockfd(-1),
                         mCallbacks(),
                         mServerMutex(),
                         mServerRunning(false),
                         mStopServer(false)
{
}

void RBPServer::Initialize()
{

    if(mSockfd > 0)
        close(mSockfd);

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, RBPPORT, &hints, &servinfo) != 0)
        throw std::runtime_error("Unable to get address info");

    for(p = servinfo; p!= NULL; p = p->ai_next)
    {
        if((mSockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1)
            continue;

        if(bind(mSockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(mSockfd);
            continue;
        }

        break;
    }

    if(p == NULL)
        throw std::runtime_error("Unable to bind to an address.");

    freeaddrinfo(servinfo);
}

void RBPServer::AddCallback(std::function<void(Command&&)> callback)
{
    if(callback)
    {
        std::lock_guard<std::mutex> lock(mServerMutex);
        mCallbacks.push_back(callback);
    }
}

void RBPServer::Start()
{
    if(mServerRunning)
        return;

    if(mSockfd == -1)
        return;

    mStopServer = false;

    std::thread t(&RBPServer::ServerThread, this);
    t.detach();
}

void RBPServer::ServerThread()
{
    mServerRunning = true;

    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof(their_addr);
    unsigned char header[5];
    int bytesRead;
    vector<unsigned char> buffer(20);

    while(!mStopServer)
    {
        bytesRead = recvfrom(mSockfd, header, 5, MSG_PEEK, (struct sockaddr*)&their_addr, &addr_len);
        if(bytesRead == -1)
            throw std::runtime_error("Receive error: header");

        int8_t startOfPacket;
        int32_t packetSize;
        unsigned char* p = header;

        rbpbufget(&startOfPacket, p, sizeof(int8_t));

        if(startOfPacket != 0x55)
            throw std::logic_error("Invalid start of packet");

        rbpbufget(&packetSize, p, sizeof(int32_t));

        if(packetSize <= 0 || packetSize > 1024)
            throw std::length_error("Invalid incoming packet size");

        buffer.resize(packetSize + 5);

        bytesRead = recvfrom(mSockfd, buffer.data(), packetSize + 5, 0, (struct sockaddr*)&their_addr, &addr_len);
        if(bytesRead == -1)
            throw std::runtime_error("Receive error: buffer");

        {
            std::lock_guard<std::mutex> lock(mServerMutex);
            for(auto& callback : mCallbacks)
                callback(Command::DecodeDataToCommand(buffer.data() + 5));
        }

        buffer.clear();
    }

    mServerRunning = false;
}

void RBPServer::Stop()
{
    if(mServerRunning)
        mStopServer = true;
}

RBPServer::~RBPServer()
{
    mStopServer = true;

    if(mSockfd > 0)
        close(mSockfd);
}

} /* raspboop */
