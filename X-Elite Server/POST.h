#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include "stdio.h"
#include <WinInet.h>
#include <windows.h>
#include <tlhelp32.h>
#pragma comment(lib, "Wininet.lib")


bool Post(const std::string& host, const std::string& path, const std::string& szPostData, std::string &data)
{
	char httpUseragent[512];
	DWORD szhttpUserAgent = sizeof(httpUseragent);

	HINTERNET hOpen = InternetOpen(httpUseragent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!hOpen)
	{
		InternetCloseHandle(hOpen);
		return false;
	}

	HINTERNET hConnect = InternetConnect(hOpen, host.c_str(), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, WININET_API_FLAG_SYNC, 0);

	if (!hConnect)
	{
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hOpen);
		return false;
	}

	static char lpszHeader[] = "Content-Type: application/x-www-form-urlencoded\r\n";
	LPCSTR lplpszTypes[2] = { "*/*", NULL };

	HINTERNET hRequest = HttpOpenRequest(hConnect, "POST", path.c_str(), NULL, NULL, lplpszTypes, INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, 0);

	if (!hRequest)
	{
		InternetCloseHandle(hRequest);
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hOpen);
		return false;
	}

	size_t hDataLength = szPostData.length();

	if (!HttpSendRequest(hRequest, lpszHeader, -1, const_cast< PCHAR >(szPostData.c_str()), static_cast< DWORD >(hDataLength)))
	{
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hOpen);
		return false;
	}

	std::string strResponse;
	const int nBuffSize = 1024;
	char buff[nBuffSize];

	BOOL bKeepReading = true;
	DWORD dwBytesRead = -1;

	while (bKeepReading && dwBytesRead != 0)
	{
		bKeepReading = InternetReadFile(hRequest, buff, nBuffSize, &dwBytesRead);
		strResponse.append(buff, dwBytesRead);
	}

	data = strResponse;

	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hOpen);

	return true;
}



