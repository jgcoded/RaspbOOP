#include <iostream>
#include <raspboop/Raspboop.h>

using namespace std;
using raspboop::RBPServer;
using raspboop::Command;

int main(int argc, char* argv[])
{
    RBPServer server;

    server.AddCallback([] (const Command* cmd, RBPServer*) {
                            cout << cmd->GetComponentId() << endl;
                            cout << cmd->GetCommandId() << endl;
                            cout << cmd->GetCommandParameters()[0] << endl;
                            cout << cmd->GetCommandParameters()[1] << endl;
                       });

    server.Start();

    return 0;
}
