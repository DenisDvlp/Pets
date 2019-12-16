#pragma once
#include <windows.h>
#include <string>

class Pipe
{
public:
	static Pipe CreateServer(std::wstring name, bool async = false);
	static Pipe CreateClient(std::wstring name);
public:
	~Pipe();

	std::wstring name() const;
	bool ok() const;
	bool connected() const;
	bool connecting();

	void connect(bool async = false);
	unsigned long send(const void* data, size_t size, bool async = false);
	unsigned long receive(void* data, size_t size, bool async = false);
	unsigned long waitResult();
	void wait();
	void disconnect();

	std::string error() const;
private:
	enum class ConnectionStatus : char
	{
		Connecting,
		Connected,
		Disconnected,
	};
	enum class Entity : char
	{
		Server,
		Client,
	};
private:
	Pipe(HANDLE, std::wstring, bool, OVERLAPPED, ConnectionStatus);
	bool resetOverlapped();
	static bool connectHelper(HANDLE pipeHandle, LPOVERLAPPED overlapped, ConnectionStatus& connectionStatus, bool async);
private:
	HANDLE m_pipeHandle = nullptr;
	std::wstring m_name;
	bool m_ok = false;
	OVERLAPPED m_overlapped{};
	ConnectionStatus m_connectionStatus = ConnectionStatus::Disconnected;
	const Entity m_entity = Entity::Server;
};

