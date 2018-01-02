#pragma once
#pragma once
#include <string>
#include < vector>

std::string base64_encode(unsigned char const*, unsigned int len);
std::vector < unsigned __int8 > base64_decode(std::string const& s);