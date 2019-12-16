#include "Pipe.h"
#include <iostream>

static const std::wstring prefix = L"//./pipe/";

Pipe::Pipe(HANDLE pipeHandle, std::wstring name, bool ok, OVERLAPPED overlapped, ConnectionStatus connectionStatus)
    : m_pipeHandle(pipeHandle)
    , m_name(name)
    , m_ok(ok)
    , m_overlapped(overlapped)
    , m_connectionStatus(connectionStatus)
{
}

Pipe::~Pipe()
{
    disconnect();
    CloseHandle(m_pipeHandle);
}

Pipe Pipe::CreateServer(std::wstring name, bool async)
{
    const auto pipeHandle = CreateNamedPipe(
        (prefix + name).c_str(),
        PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_BYTE,
        PIPE_UNLIMITED_INSTANCES,
        0, 0, 0, NULL
    );

    auto overlapped = OVERLAPPED{};
    ConnectionStatus connectionStatus = ConnectionStatus::Disconnected;

    auto success = pipeHandle != INVALID_HANDLE_VALUE;
    if (success)
    {
        success = connectHelper(pipeHandle, &overlapped, connectionStatus, async);
    }

    //it is better to use NRVO, but it does not work in Debug,
    //so use NVO otherwise which does work
    return { pipeHandle, std::move(name), success, overlapped, connectionStatus };
}

Pipe Pipe::CreateClient(std::wstring name)
{
    const auto pipeHandle = CreateFile(
        (prefix + name).c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED, NULL
    );

    const auto success = pipeHandle != INVALID_HANDLE_VALUE;
    ConnectionStatus connectionStatus = success ? ConnectionStatus::Connected : ConnectionStatus::Disconnected;

    //it is better to use NRVO, but it does not work in Debug,
    //so use NVO otherwise which does work
    return { pipeHandle, std::move(name), success, OVERLAPPED{}, connectionStatus };
}

std::wstring Pipe::name() const
{
    return m_name;
}

bool Pipe::ok() const
{
    return m_ok;
}

bool Pipe::connected() const
{
    return m_connectionStatus == ConnectionStatus::Connected;
}

bool Pipe::connecting()
{
    return m_connectionStatus == ConnectionStatus::Connecting;
}

void Pipe::connect(bool async)
{
    m_ok = connected() || connecting() ||
        connectHelper(m_pipeHandle, &m_overlapped, m_connectionStatus, async);
}

unsigned long Pipe::send(const void* data, size_t size, bool async)
{
    unsigned long numberOfBytesWritten = 0;

    m_ok = resetOverlapped();

    if (m_ok)
    {
        auto dummy = 0UL;
        m_ok = WriteFile(m_pipeHandle, data, size, &dummy, &m_overlapped) ||
            GetLastError() == ERROR_IO_PENDING;

        if (m_ok && !async)
        {
            numberOfBytesWritten = waitResult();
        }
    }

    return numberOfBytesWritten;
}

unsigned long Pipe::receive(void* data, size_t size, bool async)
{
    unsigned long numberOfBytesRead = 0;

    m_ok = resetOverlapped();

    if (m_ok)
    {
        auto dummy = 0UL;
        m_ok = ReadFile(m_pipeHandle, data, size, &dummy, &m_overlapped) ||
            GetLastError() == ERROR_IO_PENDING;

        if (m_ok && !async)
        {
            numberOfBytesRead = waitResult();
        }
    }

    return numberOfBytesRead;
}

unsigned long Pipe::waitResult()
{
    unsigned long numberOfBytesTransferred = 0;

    m_ok = GetOverlappedResult(m_pipeHandle, &m_overlapped, &numberOfBytesTransferred, TRUE);
    
    if (connecting())
    {
        m_connectionStatus = m_ok ? ConnectionStatus::Connected : ConnectionStatus::Disconnected;
    }

    if (!m_ok && GetLastError() == ERROR_BROKEN_PIPE)
    {
        disconnect();
    }

    return numberOfBytesTransferred;
}

void Pipe::wait()
{
    m_ok = WaitForSingleObject(m_overlapped.hEvent, INFINITE) == WAIT_OBJECT_0;

    if (connecting())
    {
        m_connectionStatus = m_ok ? ConnectionStatus::Connected : ConnectionStatus::Disconnected;
    }

    if (!m_ok && GetLastError() == ERROR_BROKEN_PIPE)
    {
        disconnect();
    }
}

void Pipe::disconnect()
{
    DisconnectNamedPipe(m_pipeHandle);
    m_connectionStatus = ConnectionStatus::Disconnected;
}

std::string Pipe::error() const
{
    char buf[256] = { 0 };

    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        buf, (sizeof(buf) / sizeof(char)), NULL);

    return buf;
}

bool Pipe::resetOverlapped()
{
    m_overlapped = OVERLAPPED{};
    m_overlapped.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    return m_overlapped.hEvent;
}

bool Pipe::connectHelper(HANDLE pipeHandle, LPOVERLAPPED overlapped, ConnectionStatus& connectionStatus, bool async)
{
    bool success = false;

    *overlapped = OVERLAPPED{};
    overlapped->hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

    success = overlapped->hEvent;

    if (success)
    {
        const auto result = ConnectNamedPipe(pipeHandle, overlapped);
        const auto error = GetLastError();

        success = !result && (error == ERROR_IO_PENDING ||
            error == ERROR_PIPE_CONNECTED && SetEvent(overlapped->hEvent));

        connectionStatus = success ? ConnectionStatus::Connecting : ConnectionStatus::Disconnected;
        if (success)
        {
            success = async || WaitForSingleObject(overlapped->hEvent, INFINITE) == WAIT_OBJECT_0;
            if (!async)
            {
                connectionStatus = success ? ConnectionStatus::Connected : ConnectionStatus::Disconnected;
            }
        }
    }

    return success;
}
