#ifndef _ALITTLE_ALittleScriptModifierElement_H_
#define _ALITTLE_ALittleScriptModifierElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptAttributeModifierElement;
class ALittleScriptAccessModifierElement;
class ALittleScriptCoroutineModifierElement;
class ALittleScriptRegisterModifierElement;

class ALittleScriptModifierElement : public ABnfNodeElement
{
public:
    ALittleScriptModifierElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptModifierElement() { }

private:
    bool m_flag_AttributeModifier = false;
    std::shared_ptr<ALittleScriptAttributeModifierElement> m_cache_AttributeModifier;
public:
    std::shared_ptr<ALittleScriptAttributeModifierElement> GetAttributeModifier();
private:
    bool m_flag_AccessModifier = false;
    std::shared_ptr<ALittleScriptAccessModifierElement> m_cache_AccessModifier;
public:
    std::shared_ptr<ALittleScriptAccessModifierElement> GetAccessModifier();
private:
    bool m_flag_CoroutineModifier = false;
    std::shared_ptr<ALittleScriptCoroutineModifierElement> m_cache_CoroutineModifier;
public:
    std::shared_ptr<ALittleScriptCoroutineModifierElement> GetCoroutineModifier();
private:
    bool m_flag_RegisterModifier = false;
    std::shared_ptr<ALittleScriptRegisterModifierElement> m_cache_RegisterModifier;
public:
    std::shared_ptr<ALittleScriptRegisterModifierElement> GetRegisterModifier();
};

#endif // _ALITTLE_ALittleScriptModifierElement_H_
