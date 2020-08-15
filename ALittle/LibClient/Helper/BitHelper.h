
#ifndef _ALITTLE_BITHELPER_H_
#define _ALITTLE_BITHELPER_H_

namespace ALittle
{

class BitHelper
{
public:
	static unsigned short TransEndian(unsigned short value);
	static unsigned int TransEndian(unsigned int value);
	static unsigned long long TransEndian(unsigned long long value);
};

} // ALittle

#endif // _ALITTLE_BITHELPER_H_
