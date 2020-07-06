#ifndef _ALITTLE_ALittleScriptConstModifierElement_H_
#define _ALITTLE_ALittleScriptConstModifierElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptKeyElement;

class ALittleScriptConstModifierElement : public ABnfNodeElement
{
public:
    ALittleScriptConstModifierElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptConstModifierElement() { }

private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptConstModifierElement_H_
