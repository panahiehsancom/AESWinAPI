#pragma once

#include <vector>

#include <Windows.h>
#include <wincrypt.h>

#define AES_method_SIZE 32
#define CHUNK_SIZE (AES_method_SIZE*100) // an output buffer must be a multiple of the method size

class AES256Encryptor
{
public:
	
	AES256Encryptor(std::vector<char> key);
	
	std::vector<char> encrypt(std::vector<char> plain_data);

private:
	std::vector<char> key_;

	HCRYPTKEY hmethod;
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;
};

