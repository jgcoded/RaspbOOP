#include "raspboop/Raspboop.h"
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define RBPPORT "9034"

namespace raspboop
{
    
RBPServer::RBPServer()
{

}

RBPServer* RBPServer::Create()
{
    RBPServer* R;
    
    R = (RBPServer*)malloc(sizeof(RBPServer));
    
    if(R == NULL)
        return NULL;
    
    new (R) RBPServer;
    
    struct addrinfo hints, *servinfo, *p;
    
    memset(&hints, 0, sizeof(hints));
    
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    
    if (getaddrinfo(NULL, RBPPORT, &hints, &servinfo) != 0) 
    {
        R->sockfd = -1;
        return R;
    }    
    
    for(p = servinfo; p!= NULL; p = p->ai_next) 
    {
        if((R->sockfd = socket(p->ai_family, p->ai_socktype, 
                p->ai_protocol)) == -1) 
        {
            continue;
        }
        
        if(bind(R->sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(R->sockfd);
            continue;
        }
        
        break;
    }
    
    if(p == NULL)
    {
        delete R;
        return NULL;
    }
    
    freeaddrinfo(servinfo);
    
    return R;
}

void RBPServer::PrintData()
{
    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof(their_addr);
    unsigned char bufsize[4];
    char buf[1024];
    int numbytes;
    printf("sockfd: %d", sockfd);
    if((numbytes = recvfrom(sockfd, bufsize, 3, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1)
    {
        perror("Receive error");
        return;
    }
    int32_t num = RBPPacket::Unpackint32(bufsize);
    
    printf("The incoming packet will be this long: %d\n", num);
    /*
    printf("listener: packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    printf("listener: packet contains \"%s\"\n", buf);
     */
}

int RBPServer::ReceivePacketData()
{
    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof(their_addr);
    unsigned char buf[1024];
    int numbytes;
    
    if((numbytes = recvfrom(sockfd, buf, 1024, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1)
    {
        perror("Receive error");
        return -1;
    }

    int8_t startOfPacket = RBPPacket::Unpackint8(buf);
    printf("SOP: %d\n", startOfPacket == 0x55);
    
    if (startOfPacket != 0x55)
        return -1;

    int32_t packetLength = RBPPacket::Unpackint32(buf + 1);
    printf("packetLength: %d\n", packetLength);
    if(packetLength < 1 || packetLength > 1024)
        return -1;

    for(int i = 5; i < 1024; ++i)
        buf[i - 5] = buf[i];
    
    buf[packetLength] = '\0';
    
    printf("numbytes: %d\n", numbytes);
    
    memcpy(this->buffer, buf, 1024);
    
    return numbytes;
}
    
RBPServer::~RBPServer()
{
    if(sockfd > 0)
        close(sockfd);
}

} /* raspboop */
