#include "stdafx.h"
#include "Stub.h"
#include "HWID.h"
#include "MiscFunc.h"
#include "AESTrans.h"
#include "Injection.h"
#include "Custom.h"


#include <Common\IOClass.h>
#include <Common\Xor.h>
#include <winsock.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "winInet.lib")

void main()
{
	char username[200];
	char password[200];
	char HWID[200];
	char buffer[200];

	std::string ver = XorStr("1.0");
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;
	SOCKET sock, client;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(25565);
	addr.sin_addr.S_un.S_addr = inet_addr(XorStr("192.168.0.66"));

	system("cls");

	IOClass::OutputWatermark();

	IOClass::OutputInfo(XorStr("Checking Connection..."));


	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult)
	{
		IOClass::OutputFatalError(XorStr("WSA Startup failed"));
	}


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
	{
		IOClass::OutputFatalError(XorStr("Invalid socket"));

	}

	iResult = connect(sock, (SOCKADDR*)&addr, sizeof(sockaddr_in));

	if (iResult)
	{
		IOClass::OutputFatalError(XorStr("Connection Failed"));
	}

	IOClass::OutputSuccess(XorStr("Connection Established!"));

	bool firstLoggin;
	if (!does_exist(XorStr("data.dat")))
	{
		IOClass::OutputInfo("We have noticed this is your first time running the client, please enter your login details: ");
		std::cout << XorStr("Username: ");
		std::cin >> username;
		std::cout << XorStr("Password: ");
		std::cin >> password;
		firstLoggin = true;

	}
	else
	{
		IOClass::OutputInfo(XorStr("Attempting Login..."));
		std::string info = readFile(XorStr("data.dat"));
		std::istringstream ss(info);
		ss >> username >> password;

	}
	char AES_key[200];
	char AES_IV[200];

	recv(sock, AES_key, 200, 0);
	recv(sock, AES_IV, 200, 0);
	send_encrypted(sock, username, AES_key, AES_IV);
	send_encrypted(sock, password, AES_key, AES_IV);
	std::string str_hwid = getHWID();
	char *c_hwid = &str_hwid[0u];
	send_encrypted(sock, c_hwid, AES_key, AES_IV);
	send_encrypted(sock, "0", AES_key, AES_IV);



	IOClass::OutputInfo(XorStr("Checking Login information..."));
	char response[200];
	std::string str_response = recv_decrypt(sock, response, AES_key, AES_IV);
	
	if (str_response == XorStr("1"))
	{
		system("cls");
		IOClass::OutputWatermark();
		IOClass::OutputSuccess(XorStr("Welcome, "), username);

		str_response = recv_decrypt(sock, response, AES_key, AES_IV);

		if (str_response == XorStr("first"))
		{
			IOClass::OutputInfo(XorStr("Please wait for a build to be generated..."));

			str_response = recv_decrypt(sock, response, AES_key, AES_IV);

			if (str_response == "1")
			{
				IOClass::OutputSuccess(XorStr("The build has been generated, please reopen the client."));
				system(XorStr("pause"));
				exit(0);
			}
			else
				IOClass::OutputFatalError(XorStr("There was an issue creating your build."));
			
		}

		else
		{
			DeleteUrlCacheEntry(buffer);
			std::vector < BYTE > decrypted = downl(buffer);
			inject(XorStr("csgo"), decrypted);
			closesocket(sock);
			exit(EXIT_SUCCESS);
		}
	}
	system("pause");
}