#ifndef _ALITTLE_ALittleScriptMethodParamDecElement_H_
#define _ALITTLE_ALittleScriptMethodParamDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodParamOneDecElement;
class ALittleScriptStringElement;

class ALittleScriptMethodParamDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodParamDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodParamDecElement() { }

private:
    bool m_flag_MethodParamOneDec = false;
    std::vector<std::shared_ptr<ALittleScriptMethodParamOneDecElement>> m_list_MethodParamOneDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptMethodParamOneDecElement>>& GetMethodParamOneDecList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptMethodParamDecElement_H_
