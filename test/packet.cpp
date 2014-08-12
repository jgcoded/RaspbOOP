#include <raspboop/Raspboop.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>

using raspboop::RBPPacket;
using raspboop::RBPPacketData;
using raspboop::Command;

using namespace std;

void PackTestBuffer(unsigned char* data)
{
    int8_t componentId = 1;
    int8_t commandId = 2;
    
    // some floats that accompany the command
    int32_t f1 = RBPPacket::Pack754(5.4f, 32, 8);
    int32_t f2 = RBPPacket::Pack754(-7.3f, 32, 8);
    
    //pack the buffer
    RBPPacket::Packint8(data, componentId);
    RBPPacket::Packint8(data + 1, commandId);
    RBPPacket::Packint32(data + 2, f1);
    RBPPacket::Packint32(data + 6, f2);
}

int main(int argc, char* argv[])
{
    
#define SIZE 11
    //Test out RBPPacket::DecodeDataToCommand
    
    // First create a test buffer that simulates incoming data
    unsigned char data[SIZE];
    memset(data, 0, sizeof(unsigned char) * SIZE);
    data[SIZE - 1] = '\0';
    
    PackTestBuffer(data);
    
    // Convert the buffer to a command
    Command* cmd = RBPPacket::DecodeDataToCommand(data);
    
    cout << "Component Id: " << cmd->GetComponentId() << endl;
    cout << "Command Id: " << cmd->GetCommandId() << endl;
    cout << "Parameter 1: " << cmd->GetCommandParameters()[0] << endl;
    cout << "Parameter 2: " << cmd->GetCommandParameters()[1] << endl;
    
    delete cmd;
    
    return 0;
}
