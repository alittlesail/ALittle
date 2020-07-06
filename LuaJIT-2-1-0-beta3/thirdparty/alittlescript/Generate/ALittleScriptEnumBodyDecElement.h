#ifndef _ALITTLE_ALittleScriptEnumBodyDecElement_H_
#define _ALITTLE_ALittleScriptEnumBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptEnumVarDecElement;
class ALittleScriptStringElement;

class ALittleScriptEnumBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptEnumBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptEnumBodyDecElement() { }

private:
    bool m_flag_EnumVarDec = false;
    std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>> m_list_EnumVarDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>>& GetEnumVarDecList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptEnumBodyDecElement_H_
