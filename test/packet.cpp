#include <raspboop/Raspboop.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace raspboop;
using namespace std;

int main(int argc, char* argv[])
{

#define SIZE (sizeof(int8_t)*2 + sizeof(float)*2)
    // First create a test buffer that simulates incoming data
    int8_t componentId = 1;
    int8_t commandId = 2;
    float f1 = 5.4f;
    float f2 = -7.3f;

    unsigned char data[SIZE];
    unsigned char* p;
    memset(data, 0, sizeof(unsigned char) * SIZE);
    p = data;

    //pack the buffer
    rbpbufset(p, &componentId, sizeof(int8_t));
    rbpbufset(p, &commandId, sizeof(int8_t));
    rbpbufset(p, &f1, sizeof(float));
    rbpbufset(p, &f2, sizeof(float));

    // Convert the buffer to a command
    Command cmd = RBPPacket::DecodeDataToCommand(data);

    cout << "Two int8_t and 2 floats" << endl;
    cout << "Buffer size: " << SIZE << endl;
    cout << "Component Id: " << cmd.GetComponentId() << endl;
    cout << "Command Id: " << cmd.GetCommandId() << endl;
    cout << "Parameter 1: " << cmd.GetCommandParameters()[0] << endl;
    cout << "Parameter 2: " << cmd.GetCommandParameters()[1] << endl;

    return 0;
}
