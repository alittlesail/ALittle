
#include "CryptHelper.h"
extern "C" {
#include "ALittle/LibCommon/ThirdParty/sha1/sha1.h"
#include "ALittle/LibCommon/ThirdParty/base64/base64.h"
}

namespace ALittle
{

static unsigned char XXTEA_KEY[] = { '5','9','5','e','f','a','a','3','e','3','d','2','6','3','6','b' };

void CryptHelper::XXTeaEncode(unsigned int* block, int len, unsigned int* key)
{
	if (len <= 1) return;

	unsigned int z = block[len-1], y = block[0], sum = 0, e, DELTA = 0x9e3779b9;
	int p, q;

	if (!key) key = (unsigned int*)XXTEA_KEY;

	q = 6 + 52 / len;
	while (q-- > 0)
	{
		sum += DELTA;
		e = (sum >> 2) & 3;
		for (p = 0; p < len-1; p++)
		{
			y = block[p+1];
			block[p] += (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (key[(p&3)^e]^z);
			z = block[p];
		}
		y = block[0];
		block[len-1] += (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (key[(p&3)^e]^z);
		z = block[len-1];
	}
}

void CryptHelper::XXTeaEncodeMemory(char* memory, int size, const char* key)
{
	if (!memory) return;

	char* real_key = 0;
	char adjust_key[16] = {0};
	if (key)
	{
		size_t key_len = strlen(key);
		for (size_t i = 0; i < key_len; ++i) adjust_key[i] = key[i];
		real_key = adjust_key;
	}

	while (size >= XXTEA_BLOCK_SIZE * sizeof(unsigned int))
	{
		XXTeaEncode((unsigned int*)memory, XXTEA_BLOCK_SIZE, (unsigned int*)real_key);
		memory += XXTEA_BLOCK_SIZE * sizeof(unsigned int);
		size -= XXTEA_BLOCK_SIZE * sizeof(unsigned int);
	}

	if (size >= sizeof(unsigned int))
		XXTeaEncode((unsigned int*)memory, size / sizeof(unsigned int), (unsigned int*)real_key);
}

void CryptHelper::XXTeaDecode(unsigned int* block, int len, unsigned int* key)
{
	if (len <= 1) return;

	unsigned int z = block[len-1], y = block[0], sum = 0, e, DELTA = 0x9e3779b9;
	int p, q;

	if (!key) key = (unsigned int*)XXTEA_KEY;

	q = 6 + 52 / len;
	sum = q*DELTA ;
	while (sum != 0)
	{
		e = (sum >> 2) & 3;
		for (p = len-1; p > 0; p--)
		{
			z = block[p-1];
			block[p] -= (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (key[(p&3)^e]^z);
			y = block[p];
		}
		z = block[len-1];
		block[0] -= (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (key[(p&3)^e]^z);
		y =  block[0];
		sum -= DELTA;
	}
}

void CryptHelper::XXTeaDecodeMemory(char* memory, int size, const char* key)
{
	if (!memory) return;
	
	char* real_key = 0;

	char adjust_key[16] = {0};
	if (key)
	{
		size_t key_len = strlen(key);
		for (size_t i = 0; i < key_len; ++i) adjust_key[i] = key[i];
		real_key = adjust_key;
	}

	while (size >= XXTEA_BLOCK_SIZE * sizeof(unsigned int))
	{
		XXTeaDecode((unsigned int*)memory, XXTEA_BLOCK_SIZE, (unsigned int*)real_key);
		memory += XXTEA_BLOCK_SIZE * sizeof(unsigned int);
		size -= XXTEA_BLOCK_SIZE * sizeof(unsigned int);
	}

	if (size >= sizeof(unsigned int))
		XXTeaDecode((unsigned int*)memory, size / sizeof(unsigned int), (unsigned int*)real_key);
}

// ¼ÆËã¹þÏ£Öµ
int CryptHelper::JSHash(const char* content)
{
	if (content == nullptr) return 0;
	int l = static_cast<int>(strlen(content));
	int h = l;
	int step = (l >> 5) + 1;

	for (int i = l; i >= step; i -= step)
	{
		h = h ^ ((h << 5) + content[i - 1] + (h >> 2));
	}
	return h;
}


void CryptHelper::Sha1(const std::string& msg, unsigned int dest[5])
{
	SHA1Context sha;
	SHA1Reset(&sha);
	SHA1Input(&sha, (const unsigned char*)msg.c_str(), (unsigned int)msg.size());
	if (!SHA1Result(&sha)) return;

	for (int i = 0; i < 5; ++i)
		dest[i] = sha.Message_Digest[i];
}

std::string CryptHelper::Base64Encode(const char* msg, int size)
{
	char* out = (char*)malloc(BASE64_ENCODE_OUT_SIZE(size));
	base64_encode((const unsigned char*)msg, size, out);
	std::string result = out;
	free(out);
	return result;
}

} // ALittle
