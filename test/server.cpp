#include <iostream>
#include <raspboop/Raspboop.h>

using namespace std;
using raspboop::RBPServer;
using raspboop::RBPPacket;
using raspboop::Command;

int main(int argc, char* argv[])
{

    RBPServer server;
    server.Initialize();
    server.Start();
    server.AddCallback([] (Command* cmd) {

                            cout << "Called!" << endl;

                       });

    sleep(60);
    server.Stop();

    cout << "Ending server" << endl;

    return 0;
}
