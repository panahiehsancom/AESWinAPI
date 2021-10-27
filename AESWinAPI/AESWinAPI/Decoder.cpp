#include "Decoder.h"

std::vector<char> Decoder::un_hex(std::vector<char> input)
{
	std::string str_input(input.data(), input.size());
	std::vector<char> output;
	for (int i = 0; i < str_input.size(); i += 2)
	{
		std::string hexstr = str_input.substr(i, 2); 
		std::stringstream ss;
		uint8_t x;
		unsigned tmp;

		ss << hexstr;
		ss >> std::hex >> tmp;
		x = tmp;

		output.push_back(x);
	}
	return output;
}
