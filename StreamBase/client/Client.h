#pragma once
#include "Pipe.h"
#include "Packet.h"
#include <vector>

//facade
class Client
{
public:
    Client(std::wstring name);
    void run();
private:
    bool sendData(DataType type, void* data, bool async = false);
    bool recieveObject(std::vector<char>&);
private:
    Pipe m_pipe;
};

