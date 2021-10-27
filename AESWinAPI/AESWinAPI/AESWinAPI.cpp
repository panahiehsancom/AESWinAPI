// AESWinAPI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <vector>

#include "AES256Decryptor.h"
#include "AES256Encryptor.h"
#include "Encoder.h"
#include "Logger.h"


int main()
{

	std::string plain_text = "Hallo, Ich bin WinAPI Encryptor";
	//convert a plain text to buffer of char array
	std::vector<char> plain_buffer(plain_text.begin(), plain_text.end());
	//create an instance of encryptor class
	std::string key = "1234567890abcdefghijkmlnopqrstuv";
	std::vector<char> key_buffer(key.begin(), key.end());
	Logger::log_to_console("********************************************************");
	Logger::log_to_console("Plain Data is :");
	Logger::log_to_console(plain_text);

	std::shared_ptr<AES256Encryptor> encryptor = std::make_shared<AES256Encryptor>(key_buffer);

	std::vector<char> cipher_data =  encryptor->encrypt(plain_buffer);
	std::vector<char> hex_cipher = Encoder::to_hex(cipher_data);
	Logger::log_to_console("--------------------------------------------------------");
	Logger::log_to_console("Cipher Hex Str is :");
	Logger::log_to_console(hex_cipher);
	Logger::log_to_console("########################################################"); 
	Logger::log_to_console("Plain Text is :");
	std::shared_ptr<AES256Decryptor> decryptor = std::make_shared<AES256Decryptor>(key_buffer);
	std::vector<char> output = decryptor->decrypt(cipher_data);
	std::string str_output(output.data(), output.size());
	Logger::log_to_console(str_output);
	return 0;
} 