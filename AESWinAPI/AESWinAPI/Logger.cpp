#include "Logger.h"

void Logger::log_to_console(std::string input)
{
	std::cout << input.c_str() << std::endl;
}

void Logger::log_to_console(std::vector<char> input)
{
	std::string str_temp(input.data(), input.size());
	log_to_console(str_temp);
}
