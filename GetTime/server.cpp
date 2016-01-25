#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <time.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#define CLIENT_ADDRESS "192.168.8.186"
#define PORT           123
#define MAXSIZE        1024
int main(int argc, char**argv)
{
	WSADATA     wsaData;
	char recvLine[MAXSIZE + 1];
	char sendLine[MAXSIZE + 1];
	SOCKET sServer,sClient;
	SOCKADDR_IN serverIN,clientIN;

	// Initialize Windows socket library
	WSAStartup(0x0202, &wsaData);
	memset(&serverIN,0,sizeof(serverIN));
	serverIN.sin_family = AF_INET;
	serverIN.sin_addr.S_un.S_addr = htonl((unsigned long)0x00000000);
	serverIN.sin_port = htons(PORT);
	//inet_pton(AF_INET,CLIENT_ADDRESS,&serverIN.sin_addr);

	sServer = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	bind(sServer,(struct sockaddr*)&serverIN,sizeof(SOCKADDR_IN));

	listen(sServer ,10);

	int len = sizeof(SOCKADDR_IN);
	SOCKET st =accept(sServer,(sockaddr *)&clientIN,&len);
	printf("Accepted client:%s:%d\n", inet_ntoa(clientIN.sin_addr), ntohs(clientIN.sin_port));
	
	while(1)
	{
		int byteNum = recv(st, recvLine, MAXSIZE, 0);
		recvLine[byteNum]='\0';
		printf("Received : %s\n", recvLine);

		printf("Send:");
		cin>>sendLine;
		send(st, sendLine, strlen(sendLine), 0);
		
	}
	system("pause");
	WSACleanup();
	return 0;
}