#ifndef RASPBOOP_COM_RBPSERVER_H
#define RASPBOOP_COM_RBPSERVER_H

#include <functional>
#include <atomic>
#include <mutex>
#include "raspboop/Raspboop.h"

namespace raspboop
{

class RBPServer
{

public:

    RBPServer();

    void Initialize();

    void AddCallback(std::function<void(Command*)> callback);

    void Start();

    void Stop();

    ~RBPServer();

private:

    void ServerThread();

    int mSockfd;
    vector<std::function<void(Command*)>> mCallbacks;
    std::atomic<bool> mServerRunning;
    std::atomic<bool> mStopServer;
    std::mutex mServerMutex;

};


} /* raspboop */

#endif	/* RASPBOOP_COM_RBPSERVER_H */
