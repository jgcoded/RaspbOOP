#include <iostream>
#include <raspboop/Raspboop.h>

using namespace std;
using namespace rbp;

int main(int argc, char* argv[])
{
    Server server;

    server.Initialize();
    server.Start();

    server.AddCallback([] (Command&& cmd) {
                            cout << cmd.GetComponentId() << endl;
                            cout << cmd.GetCommandId() << endl;
                            cout << cmd.GetCommandParameters()[0] << endl;
                            cout << cmd.GetCommandParameters()[1] << endl;
                       });
    // Run for 60 seconds
    sleep(60);
    server.Stop();

    return 0;
}
