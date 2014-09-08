// A modification of Beej's talker
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <raspboop/Raspboop.h>
#include <iostream>
#include <cstring>
#include <algorithm>

using raspboop::RBPPacket;
using raspboop::Command;

using namespace std;

#define SERVERPORT "9034"    // the port users will be connecting to

void PackTestBuffer(unsigned char* data)
{
    int8_t componentId = 1;
    int8_t commandId = 2;
    
    // some floats that accompany the command
    int32_t f1 = RBPPacket::Pack754(5.4f, 32, 8);
    int32_t f2 = RBPPacket::Pack754(-7.3f, 32, 8);
    
    //pack the buffer
    RBPPacket::Packint8(data, 0x55);
    RBPPacket::Packint32(data + 1, 10);
    RBPPacket::Packint8(data + 5, componentId);
    RBPPacket::Packint8(data + 6, commandId);
    RBPPacket::Packint32(data + 7, f1);
    RBPPacket::Packint32(data + 11, f2);
}

int main(int argc, char *argv[])
{
#define SIZE 15
    
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    
    unsigned char data[SIZE];
    memset(data, 0, sizeof(unsigned char) * SIZE);
    data[SIZE - 1] = '\0';
    
    PackTestBuffer(data);

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to bind socket\n");
        return 2;
    }

    if ((numbytes = sendto(sockfd, data, SIZE, 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }

    freeaddrinfo(servinfo);

    printf("client: sent %d bytes to %s\n", numbytes, argv[1]);
    close(sockfd);

    return 0;
}

