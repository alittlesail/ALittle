#ifndef _ALITTLE_ALittleScriptIdElement_H_
#define _ALITTLE_ALittleScriptIdElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptRegexElement;

class ALittleScriptIdElement : public ABnfNodeElement
{
public:
    ALittleScriptIdElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptIdElement() { }

private:
    bool m_flag_Regex = false;
    std::shared_ptr<ALittleScriptRegexElement> m_cache_Regex;
public:
    std::shared_ptr<ALittleScriptRegexElement> GetRegex();
};

#endif // _ALITTLE_ALittleScriptIdElement_H_
