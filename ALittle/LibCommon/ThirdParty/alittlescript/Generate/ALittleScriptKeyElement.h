#ifndef _ALITTLE_ALittleScriptKeyElement_H_
#define _ALITTLE_ALittleScriptKeyElement_H_

#include "../../alanguage/Model/ABnfKeyElement.h"

class ALittleScriptKeyElement : public ABnfKeyElement
{
public:
    ALittleScriptKeyElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfKeyElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptKeyElement() { }
};

#endif // _ALITTLE_ALittleScriptKeyElement_H_
