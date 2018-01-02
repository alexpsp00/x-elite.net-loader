#pragma once

#include <Windows.h>
#include <iostream>
#include <WinInet.h>
#pragma comment(lib, "Wininet.lib")
namespace FTP
{
	void UploadBuild(char * username, char * uploadName)
	{
		HINTERNET hInternet;
		HINTERNET hFtpSession;
		hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		if (hInternet == NULL)
		{
			std::cout << "Error: " << GetLastError();
		}
		else
		{
			hFtpSession = InternetConnect(hInternet, "185.62.188.4", INTERNET_DEFAULT_FTP_PORT, "USERNAME", "t;Xn(klSX-g}", INTERNET_SERVICE_FTP, 0, 0);
			if (hFtpSession == NULL)
			{
				std::cout << "Error: " << GetLastError();
			}
			else
			{

				char fileName[512];
				sprintf(fileName, "build_%s.txt", username);
				if (!FtpPutFile(hFtpSession, uploadName, fileName, FTP_TRANSFER_TYPE_BINARY, 0))
				{
					std::cout << "Error: " << GetLastError();
				}
			}
		}
	}
}