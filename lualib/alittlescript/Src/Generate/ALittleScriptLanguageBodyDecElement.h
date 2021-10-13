#ifndef _ALITTLE_ALittleScriptLanguageBodyDecElement_H_
#define _ALITTLE_ALittleScriptLanguageBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptLanguageNameDecElement;
class ALittleScriptStringElement;

class ALittleScriptLanguageBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptLanguageBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptLanguageBodyDecElement() { }

private:
    bool m_flag_LanguageNameDec = false;
    std::vector<std::shared_ptr<ALittleScriptLanguageNameDecElement>> m_list_LanguageNameDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptLanguageNameDecElement>>& GetLanguageNameDecList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptLanguageBodyDecElement_H_
