#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h> 
#include <vector> 

class NetworkClient
{ 
	enum
	{
		CHUNKSIZE = 512,
		BUFFSIZE = 16384
	};

	SOCKET tcpSocket = INVALID_SOCKET;
	char sendbuffer[BUFFSIZE];
	int  send_len = 0;

	char recvbuffer[BUFFSIZE];
	int  recv_len = 0;

public:

	class Listiner
	{
	public:
		virtual void OnDataRecievd(void* data, int size) = 0;
	};

	Listiner* listiner = nullptr;

	int  id = -1;
	bool Connect(const char* ip, int port);
	void SetSocket(int id, SOCKET tcpSocket);
	void Send(void* data, int len);
	void Recive();
	void Update();
};

class NetworkServer
{
	SOCKET listenSocket = INVALID_SOCKET;
	std::vector<NetworkClient*> clients;
	int client_id = 0;

public:

	bool Start(const char* ip, int port);
	void Update();
	void Send2Client(int id, void* data, int len);
	void Send2All(void* data, int len);
};