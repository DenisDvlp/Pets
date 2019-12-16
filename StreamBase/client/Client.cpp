#include "Client.h"
#include "Packet.h"
#include "CustomTypes.h"
#include <iostream>

void log(const char* text)
{
	std::cout << text << std::endl;
}

Client::Client(std::wstring name)
	: m_pipe(Pipe::CreateClient(std::move(name)))
{
}

void Client::run()
{
    if (!m_pipe.connected())
    {
        log(m_pipe.error().c_str());
        return;
    }
    log("Connected");
    log("Run client.");

    bool operationSuccess = false;

    char c = 'Z';
    double d = 2.3456;
    std::string s("a string from the client");
    Object_2 o2;
    o2.x[0] = 42;
    o2.x[1] = 43;
    Object_3 o3;
    o3.x[0] = 7;
    o3.x[1] = 8;
    o3.x[2] = 9;
    o3.s = "a string inside Object_3 from the client";

    operationSuccess =
        sendData(DataType::Int8, &c)   &&
        sendData(DataType::Double, &d) &&
        sendData(DataType::String, &s) &&
        sendData(DataType::Object_2, &o2);

    if (!operationSuccess)
    {
        log(m_pipe.error().c_str());
        return;
    }

    operationSuccess = sendData(DataType::Object_3, &o3, true); // flag async = true

    if (!operationSuccess)
    {
        log(m_pipe.error().c_str());
        return;
    }

    log("Do some async work");
    Sleep(1000);

    const auto sentBytes = m_pipe.waitResult();
    std::cout << "Bytes sent:" << sentBytes << std::endl;


    //request to server to create and store an instance of custom class
    auto requestedCustomClass = DataType::Object_3;
    operationSuccess = sendData(DataType::Request, &requestedCustomClass);

    if (!operationSuccess)
    {
        log(m_pipe.error().c_str());
        return;
    }

    std::vector<char> buffer;
    operationSuccess = recieveObject(buffer);

    if (!operationSuccess)
    {
        log(m_pipe.error().c_str());
        return;
    }

    Object_3 obj3;
    obj3.deserialize(buffer.data(), buffer.size());
    obj3.print();
}

bool Client::sendData(DataType type, void* data, bool async)
{
    std::cout << "Sending " << dataTypeStr[type] << "..." << std::endl;

    Packet packet;
    packet.type = type;

    if (packet.isTrivial() || packet.isRequest())
    {
        //long double is the biggest type to affect all the bytes while copying
        packet.ld = *reinterpret_cast<long double*>(data);
    }

    std::vector<char> serializedData;

    if (packet.isComplex())
    {
        serializedData = serialize(type, data);
        packet.size = serializedData.size();
    }

    const auto count = m_pipe.send(&packet, sizeof(Packet));

    if (!m_pipe.ok())
    {
        log(m_pipe.error().c_str());
        return false;
    }

    if (packet.isComplex())
    {
        const auto count = m_pipe.send(serializedData.data(), serializedData.size(), async);

        if (!m_pipe.ok())
        {
            log(m_pipe.error().c_str());
            return false;
        }
    }

    return true;
}

bool Client::recieveObject(std::vector<char>& buffer)
{
    Packet packet;
    auto c = m_pipe.receive(&packet, sizeof(Packet));

    if (!m_pipe.ok())
    {
        return false;
    }
    if (!packet.isValid())
    {
        log("Error. Packet invalid");
        return false;
    }

    if (packet.isComplex())
    {
        buffer.resize(packet.size);

        const auto readBytes = m_pipe.receive(buffer.data(), buffer.size());

        if (!m_pipe.ok() && readBytes != buffer.size())
        {
            buffer.clear();
            return false;
        }
    }

    return true;
}
