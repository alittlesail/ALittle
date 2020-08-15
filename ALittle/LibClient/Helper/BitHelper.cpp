
#include "BitHelper.h"

namespace ALittle
{

unsigned short BitHelper::TransEndian( unsigned short value )
{
	unsigned short result = 0;
	result = (value & 0x00FF) << 8;
	result = result | ((value & 0xFF00) >> 8);
	return result;
}

unsigned int BitHelper::TransEndian( unsigned int value )
{
	unsigned int result = 0;
	result = (value & 0x000000FF) << 24;
	result = result | ((value & 0x0000FF00) << 8);
	result = result | ((value & 0x00FF0000) >> 8);
	result = result | ((value & 0xFF000000) >> 24);
	return result;
}

unsigned long long BitHelper::TransEndian( unsigned long long value )
{
	unsigned long long result = 0;
	result = result | ((value & 0x00000000000000FF) << 56);
	result = result | ((value & 0x000000000000FF00) << 40);
	result = result | ((value & 0x0000000000FF0000) << 24);
	result = result | ((value & 0x00000000FF000000) << 8);
	result = result | ((value & 0x000000FF00000000) >> 8);
	result = result | ((value & 0x0000FF0000000000) >> 24);
	result = result | ((value & 0x00FF000000000000) >> 40);
	result = result | ((value & 0xFF00000000000000) >> 56);
	return result;
}

} // ALittle
