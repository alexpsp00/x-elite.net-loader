#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include <WinInet.h>
#include <vector>
#include "Base64.h"
#include "Custom.h"


#pragma comment(lib, "Wininet")

extern std::string RandomString(int len);
extern inline bool exist(const std::string& name);
extern void CryptFile(char * filename, char * output);
extern void UploadBuild(char * username, char * uploadName);



