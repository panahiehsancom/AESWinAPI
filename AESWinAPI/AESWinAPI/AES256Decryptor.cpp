#include "AES256Decryptor.h"

AES256Decryptor::AES256Decryptor(std::vector<char> key) : key_(key)
{
	DWORD dwStatus = 0;
	wchar_t info[] = L"Microsoft Enhanced RSA and AES Cryptographic Provider";

	if (!CryptAcquireContextW(&hProv, NULL, info, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
		dwStatus = GetLastError();
		//printf("CryptAcquireContext failed: %x\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		return;
	}

	if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
		dwStatus = GetLastError();
		//printf("CryptCreateHash failed: %x\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		return;
	}

	if (!CryptHashData(hHash, (BYTE*)key_.data(), key_.size(), 0)) {
		DWORD err = GetLastError();
		//printf("CryptHashData Failed : %#x\n", err);

		return;
	}
	//printf("[+] CryptHashData Success\n"); 
	if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hKey)) {
		dwStatus = GetLastError();
		//printf("CryptDeriveKey failed: %x\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		return;
	}
}

std::vector<char> AES256Decryptor::decrypt(std::vector<char> cipher_data)
{
	std::vector<char> dec_data;
	DWORD dwStatus = 0;
	BOOL bResult = FALSE;
	wchar_t info[] = L"Microsoft Enhanced RSA and AES Cryptographic Provider";
	const size_t chunk_size = CHUNK_SIZE;
	BYTE chunk[chunk_size] = { 0 };
	DWORD out_len = 0;

	BOOL isFinal = FALSE;
	DWORD readTotalSize = 0;

	DWORD inputSize = cipher_data.size();
	int index = 0;
	while (index < inputSize)
	{
		if (index + chunk_size < inputSize)
		{
			std::copy(cipher_data.data() + index, cipher_data.data() + index + chunk_size, chunk);
			index += chunk_size;
			out_len = CHUNK_SIZE;
		}
		else
		{
			int remaining_size = inputSize - index;
			std::copy(cipher_data.data() + index, cipher_data.data() + index + remaining_size, chunk);
			out_len = remaining_size;
			index += remaining_size;
			isFinal = TRUE;
		}
		if (!CryptDecrypt(hKey, 0, isFinal, 0, chunk, &out_len))
		{
			//	printf("[-] CryptDecrypt failed\n");
			std::vector<char> fail_temp;
			return fail_temp;
		}
		std::vector<char> temp(chunk, chunk + out_len);
		dec_data.insert(std::end(dec_data), temp.begin(), temp.end());
		memset(chunk, 0, chunk_size);
	}
	return dec_data;
}
