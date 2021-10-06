
#ifndef _ALITTLE_ABNFSTRINGELEMENT_H_
#define _ALITTLE_ABNFSTRINGELEMENT_H_

#include "ABnfLeafElement.h"

class ABnfStringElement : public ABnfLeafElement
{
public:
    ABnfStringElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& value)
        : ABnfLeafElement(factory, file, line, col, offset, value)
    { }
    virtual ~ABnfStringElement() = default;
    virtual const std::string& GetLeafType() override { static std::string type = "String"; return type; }
};

#endif // _ALITTLE_ABNFSTRINGELEMENT_H_