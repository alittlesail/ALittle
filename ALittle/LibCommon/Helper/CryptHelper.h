
#ifndef _ALITTLE_CRYPTHELPER_H_
#define _ALITTLE_CRYPTHELPER_H_

#include <string>

namespace ALittle
{

class CryptHelper
{
public:
	/**
	* Crypt block by XXTEA.
	* Params:
	*   block - block of input data
	*   len   - length of block, use XXTEA_BLOCK_SIZE
	*   key   - 128b key
	*/
#define XXTEA_BLOCK_SIZE 128
	static void XXTeaEncode(unsigned int* block, int len, unsigned int* key);
	static void XXTeaEncodeMemory(char* memory, int size, const char* key);

	/**
	* Decrypt block by XXTEA.
	* Params:
	*   block - block of encrypted data
	*   len   - length of block, use XXTEA_BLOCK_SIZE
	*   key   - 128bit key
	*/
	static void XXTeaDecode(unsigned int* block, int len, unsigned int* key);
	static void XXTeaDecodeMemory(char* memory, int size, const char* key);

	// ¼ÆËã¹þÏ£Öµ
	static int JSHash(const char* content);

	static void Sha1(const std::string& msg, unsigned int dest[5]);
	static std::string Base64Encode(const char* msg, int size);
};

} // ALittle

#endif // _ALITTLE_CRYPTHELPER_H_
