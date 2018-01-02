#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

extern std::string getHWID();


extern bool replace(std::string& str, const std::string& from, const std::string& to);



extern std::string format_string(std::string format, int argc, ...);

