#ifndef RASPBOOP_COM_RBPSERVER_H
#define RASPBOOP_COM_RBPSERVER_H

#include "raspboop/Raspboop.h"

namespace raspboop
{

class RBPServer
{

public:
    
    RBPServer();
    
    static RBPServer* Create();
    
    void PrintData();

    int ReceivePacketData();

    unsigned char* GetBuffer() { return buffer; }
    
    ~RBPServer();
    
private:

    int sockfd;
    unsigned char buffer[1024];
    
};


} /* raspboop */

#endif	/* RASPBOOP_COM_RBPSERVER_H */
