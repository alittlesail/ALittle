#ifndef _ALITTLE_ALittleScriptStringElement_H_
#define _ALITTLE_ALittleScriptStringElement_H_

#include "../../alanguage/Model/ABnfStringElement.h"

class ALittleScriptStringElement : public ABnfStringElement
{
public:
    ALittleScriptStringElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfStringElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStringElement() { }
};

#endif // _ALITTLE_ALittleScriptStringElement_H_
