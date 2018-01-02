#include "stdafx.h"
#include "MiscFunc.h"


inline bool does_exist(const std::string& filename)
{
	return GetFileAttributes(filename.c_str()) != INVALID_FILE_ATTRIBUTES;
}	


std::string readFile(char * name)
{
	std::string string;
	std::ifstream infile;
	infile.open(name);
	while (!infile.eof()) // To get you all the lines.
	{
		std::getline(infile, string); // Saves the line in STRING.
		return string;
	}
	infile.close();
}