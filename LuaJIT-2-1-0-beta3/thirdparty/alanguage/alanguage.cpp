
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "alanguage.h"
#include "Model/ABnf.h"
#include "Index/ABnfProject.h"

void* create_abnf()
{
	return new ABnf();
}

const char* abnf_load(void* abnf, const char* buffer, void* factory)
{
	static std::string error;
	error.clear();
	if (((ABnf*)abnf)->Load(buffer, (ABnfFactory*)factory, error))
		return nullptr;
	return error.c_str();
}

void delete_abnf(void* abnf)
{
	delete ((ABnf*)abnf);
}
