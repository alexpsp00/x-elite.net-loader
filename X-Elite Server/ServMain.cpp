#include <iostream>
#include <winsock.h>
#include <Windows.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <process.h>    /* _beginthread, _endthread */  
#include <Common\IOClass.h>
#include <ShellAPI.h>
#include <string>

#include "AESTrans.h"
#include "AES.h"
#include "Misc.h"
#include "POST.h"
#include "ftp.h"

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib,"ws2_32.lib" )

unsigned int __stdcall  ServClient(void *data);

int main()
{

	SetConsoleTitle("X-Elite");
	IOClass::OutputWatermark();
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;
	SOCKET sock, client;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(25565);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.66");


	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//2.2 

	if (iResult)
	{
		printf("WSA startup failed");
		return 0;
	}


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
	{
		printf("Invalid socket");
		return 0;
	}

	
	iResult = listen(sock, SOMAXCONN);

	if (iResult)
	{

		printf("iResult failed %u", GetLastError());
		system("pause");
		return 0;
	}

	while (client = accept(sock, 0, 0))
	{
		if (client == INVALID_SOCKET)
		{
			printf("invalid client socket", GetLastError());

			continue;
		}
		_beginthreadex(0, 0, ServClient, (void*)&client, 0, 0);


	}


	return 0;
}




unsigned int __stdcall ServClient(void *data)
{
	SOCKET* client = (SOCKET*)data;
	SOCKET Client = *client;
	char buff[200];
	char Username[200];
	char username[200];
	char password[200];
	char hwid[200];
	char flag[200];

	IOClass::OutputInfo("Client Connected");


	std::string AES_Key;
	AES_Key = RandomString(32);

	std::string AES_IV;
	AES_IV = RandomString(32);


	send(Client, AES_Key.c_str(), 200, 0);
	send(Client, AES_IV.c_str(), 200, 0);


	std::string str_username = recv_decrypt(Client, username, AES_Key, AES_IV);
	std::string str_password = recv_decrypt(Client, password, AES_Key, AES_IV);
	std::string str_hwid = recv_decrypt(Client, hwid, AES_Key, AES_IV);
	std::string str_flag = recv_decrypt(Client, flag, AES_Key, AES_IV);


	IOClass::OutputDebug("Username: " , str_username);
	IOClass::OutputDebug("Password: ", str_password);
	IOClass::OutputDebug("HWID: ", str_hwid);
	IOClass::OutputDebug("Flag: ", str_flag);


	bool isLoggedIn;
	char postrequest[512];
	std::string szResponse;
	sprintf(postrequest, "u=%s&p=%s&f=%s&h=%s", str_username.c_str(), str_password.c_str(), str_flag.c_str(), str_hwid.c_str());

	Post("URL", "server/api/public/index.php", postrequest, szResponse);

	if (szResponse == "2") // invalid HWID
	{

	}
	else if (szResponse != "1") // login incorrect
	{
		IOClass::OutputError(str_username, "Error logging in");
		send_encrypted(Client, "0", AES_Key, AES_IV);
		closesocket(Client);
	}
	else
	{
		send_encrypted(Client, "1", AES_Key, AES_IV);
		isLoggedIn = true;
		IOClass::OutputSuccess(str_username, "is Logged in");
		
		IOClass::OutputInfo("Sending Build");

		if (isLoggedIn)
		{
			char VMPCommand[200];
			char fileName[200];
			char VMPfile[200];
			char URL[200];

			if (szResponse == "1") //normal build
			{
				sprintf(URL, "http://URL.com/builds/cheat_builds/build_%s.txt", str_username.c_str());
				sprintf(fileName, "build_%s.txt", str_username.c_str());
				sprintf(VMPCommand, "VMProtect_Con Build.dll VMP_build_%s.dll -pf mutate.vmp", str_username.c_str());
				sprintf(VMPfile, "VMP_build_%s.dll", str_username.c_str());


				
			}
			if (!exist(fileName))
			{
				send_encrypted(Client, "first", AES_Key, AES_IV);
				IOClass::OutputInfo("Generating First Build");
				system(VMPCommand);
				CryptFile(VMPfile, fileName);
				FTP::UploadBuild(username, fileName);
				send_encrypted(Client, "1", AES_Key, AES_IV);

			}
			else
			{
				send_encrypted(Client, URL, AES_Key, AES_IV);
			}

			IOClass::OutputInfo("Build sent to ", str_username);
			closesocket(Client);
		}

	}
	return 0;

}
