#ifndef _ALITTLE_ALittleScriptAttributeModifierElement_H_
#define _ALITTLE_ALittleScriptAttributeModifierElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptNativeModifierElement;
class ALittleScriptCommandModifierElement;
class ALittleScriptLanguageModifierElement;
class ALittleScriptConstModifierElement;
class ALittleScriptNullableModifierElement;
class ALittleScriptProtocolModifierElement;
class ALittleScriptStringElement;

class ALittleScriptAttributeModifierElement : public ABnfNodeElement
{
public:
    ALittleScriptAttributeModifierElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptAttributeModifierElement() { }

private:
    bool m_flag_NativeModifier = false;
    std::shared_ptr<ALittleScriptNativeModifierElement> m_cache_NativeModifier;
public:
    std::shared_ptr<ALittleScriptNativeModifierElement> GetNativeModifier();
private:
    bool m_flag_CommandModifier = false;
    std::shared_ptr<ALittleScriptCommandModifierElement> m_cache_CommandModifier;
public:
    std::shared_ptr<ALittleScriptCommandModifierElement> GetCommandModifier();
private:
    bool m_flag_LanguageModifier = false;
    std::shared_ptr<ALittleScriptLanguageModifierElement> m_cache_LanguageModifier;
public:
    std::shared_ptr<ALittleScriptLanguageModifierElement> GetLanguageModifier();
private:
    bool m_flag_ConstModifier = false;
    std::shared_ptr<ALittleScriptConstModifierElement> m_cache_ConstModifier;
public:
    std::shared_ptr<ALittleScriptConstModifierElement> GetConstModifier();
private:
    bool m_flag_NullableModifier = false;
    std::shared_ptr<ALittleScriptNullableModifierElement> m_cache_NullableModifier;
public:
    std::shared_ptr<ALittleScriptNullableModifierElement> GetNullableModifier();
private:
    bool m_flag_ProtocolModifier = false;
    std::shared_ptr<ALittleScriptProtocolModifierElement> m_cache_ProtocolModifier;
public:
    std::shared_ptr<ALittleScriptProtocolModifierElement> GetProtocolModifier();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptAttributeModifierElement_H_
