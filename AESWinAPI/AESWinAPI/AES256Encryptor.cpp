#include "AES256Encryptor.h"

AES256Encryptor::AES256Encryptor(std::vector<char> key):key_(key)
{
	WORD dwStatus = 0;
	wchar_t info[] = L"Microsoft Enhanced RSA and AES Cryptographic Provider";

	if (!CryptAcquireContextW(&hProv, NULL, info, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
		dwStatus = GetLastError();
		//printf("CryptAcquireContext failed: %x\n", dwStatus);
		printf("failed 12 : %x\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		return;
	}

	if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
		dwStatus = GetLastError();
		//printf("CryptCreateHash failed: %x\n", dwStatus);
		printf("failed 20 : %x\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		return;
	}

	if (!CryptHashData(hHash, (BYTE*)key_.data(), key_.size(), 0)) {
		DWORD err = GetLastError();
		//printf("CryptHashData Failed : %#x\n", err);
		printf("Failed 28: %#x\n", err);

		return;
	}
	//printf("[+] CryptHashData Success\n");

	if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hmethod)) {
		dwStatus = GetLastError();
		//printf("CryptDerivemethod failed: %x\n", dwStatus);
		printf("failed 37: %x\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		return;
	}
}

std::vector<char> AES256Encryptor::encrypt(std::vector<char> plain_data)
{
	std::vector<char> cipher_data;
	const size_t chunk_size = CHUNK_SIZE;
	BYTE chunk[CHUNK_SIZE * 2] = { 0 };
	DWORD out_len = 0;

	BOOL isFinal = FALSE;
	DWORD readTotalSize = 0;

	DWORD inputSize = plain_data.size();
	int index = 0;
	while (index < inputSize)
	{
		if (index + chunk_size < inputSize)
		{
			std::copy(plain_data.data() + index, plain_data.data() + index + chunk_size, chunk);
			index += chunk_size;
			out_len = CHUNK_SIZE;
		}
		else
		{
			int remaining_size = inputSize - index;
			std::copy(plain_data.data() + index, plain_data.data() + index + remaining_size, chunk);
			out_len = remaining_size;
			index += remaining_size;
			isFinal = TRUE;
		}
		if (!CryptEncrypt(hmethod, NULL, isFinal, 0, chunk, &out_len, CHUNK_SIZE * 2)) {
			DWORD dwErrorCode = GetLastError();
			wchar_t szTemp[100];
			//wsprintf(szTemp, L"%d", dwErrorCode);
			//printf("[-] failed 76\n");
			break;
		}
		std::vector<char> temp(chunk, chunk + out_len);
		cipher_data.insert(std::end(cipher_data), temp.begin(), temp.end());
		memset(chunk, 0, chunk_size);
	}
	return cipher_data;
}

