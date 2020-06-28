
#ifndef _ALITTLE_ABNFFILECLASS_H_
#define _ALITTLE_ABNFFILECLASS_H_

#include "ALittle/LibCommon/ThirdParty/alanguage/Index/ABnfFile.h"

class ABnfFileClass : public ABnfFile
{
public:
	ABnfFileClass(ABnfProject* project, const std::string& full_path, ABnf* abnf, const char* text, size_t len);
};

#endif // _ALITTLE_ABNFFILECLASS_H_
