#ifndef _ALITTLE_ALittleScriptRegexElement_H_
#define _ALITTLE_ALittleScriptRegexElement_H_

#include "../../alanguage/Model/ABnfRegexElement.h"

class ALittleScriptRegexElement : public ABnfRegexElement
{
public:
    ALittleScriptRegexElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type, std::shared_ptr<std::regex> regex)
        : ABnfRegexElement(factory, file, line, col, offset, type, regex) { }
    virtual ~ALittleScriptRegexElement() { }
};

#endif // _ALITTLE_ALittleScriptRegexElement_H_
