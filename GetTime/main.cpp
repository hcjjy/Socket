//main.cpp
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <time.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#define SERVER_ADDRESS "192.168.8.186"//sometimes may change.you can go http://www.pool.ntp.org/zone/cn							
#define PORT           123
#define MAXSIZE        1024
int main(int argc, char**argv)
{
	WSADATA     wsaData;

	SOCKET sClient ;
	int n,t;
	char recvLine[MAXSIZE + 1];
	char sendLine[MAXSIZE + 1];
	SOCKADDR_IN serverIN;

	// Initialize Windows socket library
	WSAStartup(0x0202, &wsaData);

	sClient =socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	memset(&serverIN,0,sizeof(serverIN));
	serverIN.sin_family = AF_INET;
	serverIN.sin_addr.S_un.S_addr = inet_addr(SERVER_ADDRESS);
	serverIN.sin_port = htons(PORT);//daytime server port

	/*if (inet_pton(AF_INET,SERVER_ADDRESS,&serverIN.sin_addr) <= 0)
	{
		cout<<"inet_pton error. "<<endl;
		system("pause");
		return -1;
	}*/
	

	while( (t = connect(sClient,(sockaddr *)&serverIN,sizeof(SOCKADDR_IN))) < 0)
	{
		cout<<"connect error. "<<t<<endl;
	}
	cout<<"successful! "<<endl;

	while (TRUE)
	{
		printf("Send:");
		cin>>sendLine;
		send(sClient, sendLine, strlen(sendLine), 0);

		int byteNum = recv(sClient, recvLine, MAXSIZE, 0);
		recvLine[byteNum]='\0';
		printf("Received : %s\n", recvLine);
	}
	
	closesocket(sClient);
	WSACleanup();
	return 0;
}