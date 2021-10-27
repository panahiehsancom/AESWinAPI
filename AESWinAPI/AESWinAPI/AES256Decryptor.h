#pragma once

#include <memory>
#include <stdio.h>
#include <vector> 

#include <Windows.h>
#include <wincrypt.h>

#define AES_KEY_SIZE 32
#define CHUNK_SIZE (AES_KEY_SIZE*3) // an output buffer must be a multiple of the key size

class AES256Decryptor
{
public:
	AES256Decryptor(std::vector<char> key);
	// Inherited via IDecryptor
	std::vector<char> decrypt(std::vector<char> cipher_data);

private:

	std::vector<char> key_;
	HCRYPTKEY hKey;
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;
};

