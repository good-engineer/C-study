#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") //원속 lib link
#define BUFLEN 1024
#define PORT 61557

int main()
{
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN fromServer;

	int rec_size;
	int fromServer_size;
	char buffer[BUFLEN];

	// Winsock
	if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR)
	{
		printf("WinSock has not intialized!\n");
		WSACleanup();
		exit(0);
	}

	memset(&fromServer, 0, sizeof(fromServer));

	fromServer.sin_family = AF_INET;
	fromServer.sin_addr.s_addr = inet_addr("192.168.0.24");
	fromServer.sin_port = htons(PORT);
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// Create socket
	if (clientSocket == INVALID_SOCKET)
	{
		printf("Socket can not be created!\n");
		closesocket(clientSocket);
		WSACleanup();
		exit(0);
	}

	fromServer_size = sizeof(fromServer);
	memset(buffer, 0, BUFLEN);

	// Keep recciveing data
	while (1)
	{
		rec_size = recvfrom(clientSocket, buffer, BUFLEN, 0, (struct sockaddr*)&fromServer, &fromServer_size);
		printf("Reccived size: %d\n", rec_size);
		printf("%s", buffer);
	}

	closesocket(clientSocket);
	WSACleanup();
	return 0;
}