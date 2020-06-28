
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
#include "abnf_c.h"
}

#include "Node/ABnfFactoryClass.h"
#include "Node/ABnfFileClass.h"

void* create_abnf_factory()
{
	return new ABnfFactoryClass();
}

void delete_abnf_factory(void* factory)
{
	delete ((ABnfFactoryClass*)factory);
}

void* create_abnf_file(const char* full_path, void* abnf, const char* text, size_t len)
{
	return new ABnfFileClass(nullptr, full_path, (ABnf*)abnf, text, len);
}

void delete_abnf_file(void* file)
{
	delete ((ABnfFileClass*)file);
}
