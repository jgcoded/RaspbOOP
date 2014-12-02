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

using namespace rbp;
using namespace std;

#define SIZE (sizeof(int8_t) + sizeof(int32_t) \
            + sizeof(int8_t)*2 + sizeof(float)*2)

#define SERVERPORT "9034"    // the port users will be connecting to

void PackTestBuffer(unsigned char* data)
{
    // First create a test buffer that simulates incoming data
    int8_t startOfPacket = 0x55;
    int32_t packetLength = sizeof(int8_t)*2 + sizeof(float)*2;
    int8_t componentId = 1;
    int8_t commandId = 2;
    float f1 = 5.4f;
    float f2 = -7.3f;

    memset(data, 0, sizeof(unsigned char) * SIZE);

    //pack the buffer
    rbpbufset(data, &startOfPacket, sizeof(int8_t));
    rbpbufset(data, &packetLength, sizeof(int32_t));
    rbpbufset(data, &componentId, sizeof(int8_t));
    rbpbufset(data, &commandId, sizeof(int8_t));
    rbpbufset(data, &f1, sizeof(float));
    rbpbufset(data, &f2, sizeof(float));
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    unsigned char data[SIZE];
    memset(data, 0, sizeof(unsigned char) * SIZE);

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

