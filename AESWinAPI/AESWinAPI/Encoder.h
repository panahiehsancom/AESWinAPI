#pragma once

#include <sstream>
#include <string>
#include <vector>

class Encoder
{
public:
	static std::vector<char> to_hex(std::vector<char> input);
};

