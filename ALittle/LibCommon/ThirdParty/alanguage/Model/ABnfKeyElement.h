
#ifndef _ALITTLE_ABNFKEYELEMENT_H_
#define _ALITTLE_ABNFKEYELEMENT_H_

#include "ABnfLeafElement.h"

class ABnfKeyElement : public ABnfLeafElement
{
public:
    ABnfKeyElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& value)
        : ABnfLeafElement(factory, file, line, col, offset, value)
    { }
    virtual ~ABnfKeyElement() {}

    virtual const std::string& GetLeafType() override { static std::string type = "Key"; return type; }
};

#endif // _ALITTLE_ABNFKEYELEMENT_H_