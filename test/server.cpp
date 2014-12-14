#include <iostream>
#include <raspboop/Raspboop.h>

using namespace std;
using namespace rbp;

int main(int argc, char* argv[])
{
    Server server;
    server.EnableAutodiscovery("0.0.0.0");
    server.AddCallback([] (const Command* cmd, Server*) {
                            cout << cmd->GetComponentId() << endl;
                            cout << cmd->GetCommandId() << endl;
                            cout << cmd->GetParameters()[0] << endl;
                            cout << cmd->GetParameters()[1] << endl;
                       });

    server.Start();
    return 0;
}
