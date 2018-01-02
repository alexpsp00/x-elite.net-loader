#pragma once

#include <iostream>
#include <string>
#include "cc.h"
#include <ctime>


using namespace std;
namespace IOClass
{

	void OutputText(std::string text1, std::string text2 = "")
	{
		std::cout << white << "[OUTPUT]  " << text1 << text2 << std::endl;
	}

	void OutputError(std::string text1, std::string text2 = "")
	{
		std::cout << red << "[ERROR]   " << text1 << text2 << std::endl;
	}
	void OutputFatalError(std::string text1, std::string text2 = "")
	{
		std::cout << red << "[ERROR]   " << text1 << text2 << std::endl << "[ERROR FATAL]" << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	void OutputWarning(std::string text1, std::string text2 = "")
	{
		std::cout << yellow << "[WARNING] " << text1 << text2 << std::endl;
	}

	void OutputDebug(std::string text1, std::string text2 = "")
	{

		std::cout << blue << "[DEBUG]   " << text1 << text2 << std::endl;

	}

	void OutputSuccess(std::string text1, std::string text2 = "")
	{
		std::cout << green << "[SUCCESS] " << text1 << text2 << std::endl;
	}

	void OutputInfo(std::string text1, std::string text2 = "")
	{
		std::cout << blue << "[INFO]    " << text1 << text2 << std::endl;
	}

	void OutputWatermark()
	{
		cout << blue;
		cout << "    ____              __        __   _             " << endl;
		cout << "   /  _/_____ ____   / /____ _ / /_ (_)____   ____ " << endl;
		cout << "   / / / ___// __ \\ / // __ `// __// // __ \\ / __ \\" << endl;
		cout << " _/ / (__  )/ /_/ // // /_/ // /_ / // /_/ // / / /" << endl;
		cout << "/___//____/ \\____//_/ \\__,_/ \\__//_/ \\____//_/ /_/ " << endl;
		cout << "                                                   " << endl;
	}


	void OutputCountdown(int seconds, std::string message, std::string text2 = "")
	{
		cout << yellow;
		cout << "[INFO]    " << message << text2 << "...";
		for (int i = seconds; i > 0; i--)
		{
			cout << i << "... ";
			Sleep(1000);
		}
		cout << endl;
	}
}