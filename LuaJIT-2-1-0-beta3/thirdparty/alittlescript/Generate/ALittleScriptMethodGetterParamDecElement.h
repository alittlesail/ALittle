#ifndef _ALITTLE_ALittleScriptMethodGetterParamDecElement_H_
#define _ALITTLE_ALittleScriptMethodGetterParamDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptStringElement;

class ALittleScriptMethodGetterParamDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodGetterParamDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodGetterParamDecElement() { }

private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptMethodGetterParamDecElement_H_
