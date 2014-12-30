#include <iostream>
#include <raspboop/Raspboop.h>

using namespace std;
using namespace rbp;

int main(int argc, char* argv[])
{
    Server server;
    server.EnableAutodiscovery("0.0.0.0");
    server.AddCallback([] (const Command* cmd, Server*) {
                            cout << "This command is for component: ";
                            cout << cmd->GetComponentId() << endl;
                            cout << "The command id is: ";
                            cout << cmd->GetCommandId() << endl;
                       });

    server.Start();
    return 0;
}
