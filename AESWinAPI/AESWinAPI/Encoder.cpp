#include "Encoder.h"

std::vector<char> Encoder::to_hex(std::vector<char> input)
{
	std::string mystr;
	for (int i = 0; i < input.size(); ++i)
	{
		std::stringstream ss;
		ss << std::hex << (int)(unsigned char)input[i];
		std::string tempval(ss.str());
		if (tempval.size() == 1)
			tempval = "0" + tempval;
		mystr += tempval;
	}
	std::vector<char> output(mystr.begin(), mystr.end());
	return output;
}

 