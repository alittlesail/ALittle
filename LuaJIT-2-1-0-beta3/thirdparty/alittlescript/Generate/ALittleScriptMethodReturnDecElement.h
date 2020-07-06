#ifndef _ALITTLE_ALittleScriptMethodReturnDecElement_H_
#define _ALITTLE_ALittleScriptMethodReturnDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodReturnOneDecElement;
class ALittleScriptStringElement;

class ALittleScriptMethodReturnDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodReturnDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodReturnDecElement() { }

private:
    bool m_flag_MethodReturnOneDec = false;
    std::vector<std::shared_ptr<ALittleScriptMethodReturnOneDecElement>> m_list_MethodReturnOneDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptMethodReturnOneDecElement>>& GetMethodReturnOneDecList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptMethodReturnDecElement_H_
