#include "stdafx.h"
#include "Injection.h"




DWORD MyGetProcessId(LPCTSTR ProcessName)
{
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hsnap, &pt)) { // must call this first
		do {
			if (!lstrcmpi(pt.szExeFile, ProcessName)) {
				CloseHandle(hsnap);
				return pt.th32ProcessID;
			}
		} while (Process32Next(hsnap, &pt));
	}
	CloseHandle(hsnap); // close handle on failure
	return 0;
}

void inject(char *processname,std::vector < BYTE > &image)
{
	sprintf(processname, "%s.exe", processname);
	DWORD FindProcessId(const std::wstring& processName);
	std::cout << "[i] Waiting for " << processname << ".exe..." << std::endl;

_Search:
	DWORD dwProcessID = MyGetProcessId(TEXT("csgo.exe"));

	if (!dwProcessID)
	{
		Sleep(300);
		goto _Search;
	}

	std::cout << "[i] Process found! Injecting...." << std::endl;
	Sleep(5000);

	Process thisProc;
	thisProc.Attach(dwProcessID);

	//std::cout << L"Manual image mapping from buffer test\n";

	if (thisProc.mmap().MapImage(image.size(), &image[0], false, CreateLdrRef))
	{

	}
	else
		std::cout << L"Successfully mapped, unmapping\n";

	thisProc.mmap().UnmapAllModules();
}
