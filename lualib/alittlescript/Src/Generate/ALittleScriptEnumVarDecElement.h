#ifndef _ALITTLE_ALittleScriptEnumVarDecElement_H_
#define _ALITTLE_ALittleScriptEnumVarDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptEnumVarNameDecElement;
class ALittleScriptNumberElement;
class ALittleScriptTextElement;
class ALittleScriptStringElement;

class ALittleScriptEnumVarDecElement : public ABnfNodeElement
{
public:
    ALittleScriptEnumVarDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptEnumVarDecElement() { }

private:
    bool m_flag_EnumVarNameDec = false;
    std::shared_ptr<ALittleScriptEnumVarNameDecElement> m_cache_EnumVarNameDec;
public:
    std::shared_ptr<ALittleScriptEnumVarNameDecElement> GetEnumVarNameDec();
private:
    bool m_flag_Number = false;
    std::shared_ptr<ALittleScriptNumberElement> m_cache_Number;
public:
    std::shared_ptr<ALittleScriptNumberElement> GetNumber();
private:
    bool m_flag_Text = false;
    std::shared_ptr<ALittleScriptTextElement> m_cache_Text;
public:
    std::shared_ptr<ALittleScriptTextElement> GetText();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptEnumVarDecElement_H_
