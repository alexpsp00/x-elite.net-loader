#include "stdafx.h"
#include "HWID.h"


bool replace(std::string& str, const std::string& from, const std::string& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

std::string format_string(std::string format, int argc, ...)
{
	std::string copy = format;
	std::vector<std::string> argv;
	va_list vl;
	va_start(vl, argc);
	for (int i = 0; i < argc; i++)
		argv.push_back(va_arg(vl, std::string));
	va_end(vl);
	for (int i = 0; i < argv.size(); i++)
		replace(copy, std::string("%").append(std::to_string(i + 1)), argv[i]);
	return copy;
}

std::string getHWID()
{
	std::string szHwProfileGuid;
	std::string szHwProfileName;
	std::string szHwHddSerialNb;
	std::string szHwMachineName;
	HW_PROFILE_INFOA hwProfileInfo;
	if (GetCurrentHwProfileA(&hwProfileInfo) != NULL)
	{
		szHwProfileGuid = std::string(hwProfileInfo.szHwProfileGuid);
		szHwProfileName = std::string(hwProfileInfo.szHwProfileName);
	}
	DWORD HddNumber = 0;
	if (GetVolumeInformationA("C://", NULL, NULL, &HddNumber, NULL, NULL, NULL, NULL))
	{
		szHwHddSerialNb = std::to_string(HddNumber);
	}
	DWORD size = MAX_PATH;
	char computername[MAX_PATH];
	if (GetComputerNameA(computername, &size))
	{
		szHwMachineName = std::string(computername);
	}
	return std::to_string(std::hash<std::string>()(format_string("%1%2%3%4", 4, szHwProfileGuid, szHwProfileName, szHwHddSerialNb, szHwMachineName)));
}	