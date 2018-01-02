#pragma once
#include <iostream>

#include "Crypto\base64.h"
#include "Crypto\cryptlib.h"
#include "Crypto\hex.h"
#include "Crypto\filters.h"
#include "Crypto\aes.h"
#include "Crypto\/modes.h"

# pragma comment ( lib, "cryptlib" )

namespace Crypt
{
	extern std::string encrypt(std::string& str_in, std::string& key, std::string& iv);
	extern std::string decrypt(std::string& str_in, std::string& key, std::string& iv);
}