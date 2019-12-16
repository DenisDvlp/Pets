#pragma once
#include "Pipe.h"
#include "Storage.h"

//facade
class Server
{
public:
    Server(std::wstring name);
    void run();
private:
    bool checkClientConnection();
    bool processNextPacket();
private:
    Pipe m_pipe;
    Storage m_storage;
    std::vector<char> m_buffer;
};

