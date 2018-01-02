#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <Shlwapi.h>



#include <Blackbone-master\src\BlackBone/Config.h>
#include <Blackbone-master\src\BlackBone/Process/Process.h>
#include <Blackbone-master\src\BlackBone/PE/PEImage.h>
#include <Blackbone-master\src\BlackBone/Misc/Utils.h>
#include <Blackbone-master\src\BlackBone/Misc/DynImport.h>


#pragma comment(lib, "Shlwapi.lib")
using namespace blackbone;

extern DWORD MyGetProcessId(LPCTSTR ProcessName);
extern void inject(char *processname, std::vector < BYTE > &image);