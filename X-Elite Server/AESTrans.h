#pragma once

#include "AES.h"
#include <winsock.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

extern char * send_encrypted(SOCKET s, char* message, std::string key, std::string iv);

extern std::string recv_decrypt(SOCKET s, char * buffer, std::string key, std::string iv);