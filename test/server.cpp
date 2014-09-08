#include <iostream>
#include <raspboop/Raspboop.h>

using namespace std;
using raspboop::RBPServer;
using raspboop::RBPPacket;
using raspboop::Command;

int main(int argc, char* argv[])
{
    
    RBPServer* server = RBPServer::Create();
    
    if(server)
        while(server->ReceivePacketData() > 0)
        {
            Command* cmd = RBPPacket::DecodeDataToCommand(server->GetBuffer());

    	    cout << "Component Id: " << cmd->GetComponentId() << endl;
            cout << "Command Id: " << cmd->GetCommandId() << endl;
            cout << "Parameter 1: " << cmd->GetCommandParameters()[0] << endl;
            cout << "Parameter 2: " << cmd->GetCommandParameters()[1] << endl;

            delete cmd;
        }
    
    delete server;
    
    cout << "Ending server" << endl;
    
    return 0;
}
