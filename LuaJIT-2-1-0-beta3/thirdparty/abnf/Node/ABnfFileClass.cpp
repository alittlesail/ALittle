
#include "ABnfFileClass.h"

ABnfFileClass::ABnfFileClass(ABnfProject* project, const std::string& full_path, ABnf* abnf, const char* text, size_t len)
	: ABnfFile(project, full_path, abnf, text, len)
{
}
