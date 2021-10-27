#pragma once

#include <iostream>
#include <string>
#include <vector>

class Logger
{
public:
	static void log_to_console(std::string input);
	static void log_to_console(std::vector<char> input);
};

