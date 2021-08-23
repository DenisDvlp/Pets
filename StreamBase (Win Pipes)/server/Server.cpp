#include "Server.h"
#include "Packet.h"
#include <iostream>

void log(const char* text)
{
    std::cout << text << std::endl;
}

Server::Server(std::wstring name)
    : m_pipe(Pipe::CreateServer(std::move(name), true))
    , m_storage()
    , m_buffer(1024)
{
    log("Initializing the server...");

    log("Do some async work");
    Sleep(1000);

    log("Initialized.");
}

void Server::run()
{
    log("Run server loop.");

    bool operationSuccess = false;

    while (true)
    {
        Sleep(100);

        operationSuccess = checkClientConnection();

        if (!operationSuccess)
        {
            log(m_pipe.error().c_str());
            break;
        }

        operationSuccess = processNextPacket();

        if (!operationSuccess)
        {
            log(m_pipe.error().c_str());

            //if client closed the connection, wait for another client
            if (!m_pipe.connected())
            {
                m_pipe.connect(true);
                continue;
            }

            break;
        }
    }
}

bool Server::checkClientConnection()
{
    if (m_pipe.connecting())
    {
        log("Waiting for a client...");

        m_pipe.wait();

        if (!m_pipe.ok())
        {
            return false;
        }

        log("Client connected");
    }

    return true;
}

bool Server::processNextPacket()
{
    Packet packet;
    m_pipe.receive(&packet, sizeof(Packet));

    if (!m_pipe.ok())
    {
        return false;
    }

    if (!packet.isValid())
    {
        log("Error. Packet invalid.");
        return false;
    }

    if (packet.isComplex())
    {
        m_buffer.resize(packet.size);

        const auto readBytes = m_pipe.receive(m_buffer.data(), m_buffer.size());

        if (!m_pipe.ok() && readBytes != m_buffer.size())
        {
            return false;
        }

        m_storage.store(packet.type, m_buffer.data(), m_buffer.size());
    }

    if (packet.isTrivial())
    {
        m_storage.store(packet.type, &packet.size, 0);
    }

    if (packet.isRequest())
    {
        auto serializedData = m_storage.construct(packet.requestDataType);

        if (!serializedData.empty())
        {
            Packet responsePacket;
            responsePacket.type = packet.requestDataType;
            responsePacket.size = serializedData.size();
            m_pipe.send(&responsePacket, sizeof(Packet));

            if (!m_pipe.ok())
            {
                return false;
            }

            m_pipe.send(serializedData.data(), serializedData.size());

            if (!m_pipe.ok())
            {
                return false;
            }
        }
    }

    return true;
}
