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


void inject(std::vector < BYTE > &image)
{

	Process thisProc;
	thisProc.Attach(GetCurrentProcessId());

	//std::cout << L"Manual image mapping from buffer test\n";

	if (!thisProc.mmap().MapImage(image.size(), &image[0], false, CreateLdrRef | RebaseProcess | NoDelayLoad))
	{

	}
	
		//std::cout << "Successfully mapped, unmapping\n";


}
