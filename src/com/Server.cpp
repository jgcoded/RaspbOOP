#include "raspboop/Raspboop.h"
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <exception>
#include <thread>

using std::int8_t;
using std::int32_t;

namespace rbp
{

#define RBP_START_OF_PACKET 0x55
#define RBP_SOP_TYPE_SIZE sizeof(int8_t)
#define RBP_PACKET_LENGTH_TYPE_SIZE sizeof(int32_t)
#define RBP_PACKET_HEADER_SIZE RBP_SOP_TYPE_SIZE + RBP_PACKET_LENGTH_TYPE_SIZE
#define RBP_PACKET_MIN_SIZE 0
#define RBP_PACKET_MAX_SIZE 1024

Server::Server() : mSockfd(-1),
                   mCallbacks(),
                   mServerMutex(),
                   mServerRunning(false),
                   mStopServer(false)
{
}

void Server::Initialize(std::string port)
{

    if(mSockfd > 0)
        close(mSockfd);

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, port.c_str(), &hints, &servinfo) != 0)
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

void Server::AddCallback(std::function<void(Command&&)> callback)
{
    if(callback)
    {
        std::lock_guard<std::mutex> lock(mServerMutex);
        mCallbacks.push_back(callback);
    }
}

void Server::Start()
{
    if(mServerRunning)
        return;

    if(mSockfd == -1)
        return;

    mStopServer = false;

    std::thread t(&Server::ServerThread, this);
    t.detach();
}

void Server::ServerThread()
{
    mServerRunning = true;

    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof(their_addr);
    unsigned char header[RBP_PACKET_HEADER_SIZE];
    int bytesRead;
    std::vector<unsigned char> buffer(20);

    while(!mStopServer)
    {
        bytesRead = recvfrom(mSockfd,
                             header,
                             RBP_PACKET_HEADER_SIZE,
                             MSG_PEEK,
                             (struct sockaddr*)&their_addr,
                             &addr_len);

        if(bytesRead == -1)
            throw std::runtime_error("Receive error: header");

        int8_t startOfPacket;
        int32_t pSize;
        unsigned char* p = header;

        rbpbufget(&startOfPacket, p, RBP_SOP_TYPE_SIZE);

        if(startOfPacket != RBP_START_OF_PACKET)
            throw std::logic_error("Invalid start of packet");

        rbpbufget(&pSize, p, RBP_PACKET_LENGTH_TYPE_SIZE);

        if(pSize <= RBP_PACKET_MIN_SIZE || pSize > RBP_PACKET_MAX_SIZE)
            throw std::length_error("Invalid incoming packet size");

        buffer.resize(pSize + RBP_PACKET_HEADER_SIZE);

        bytesRead = recvfrom(mSockfd,
                             buffer.data(),
                             pSize + RBP_PACKET_HEADER_SIZE,
                             0,
                             (struct sockaddr*)&their_addr,
                             &addr_len);

        if(bytesRead == -1)
            throw std::runtime_error("Receive error: buffer");

        {
            std::lock_guard<std::mutex> lock(mServerMutex);
            for(auto& callback : mCallbacks)
                callback(Command::DecodeDataToCommand(buffer.data() + RBP_PACKET_HEADER_SIZE));
        }

        buffer.clear();
    }

    mServerRunning = false;
}

void Server::Stop()
{
    if(mServerRunning)
        mStopServer = true;
}

Server::~Server()
{
    mStopServer = true;

    if(mSockfd > 0)
        close(mSockfd);
}

} /* rbp */
