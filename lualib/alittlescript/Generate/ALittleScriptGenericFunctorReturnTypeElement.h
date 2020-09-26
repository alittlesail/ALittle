#ifndef _ALITTLE_ALittleScriptGenericFunctorReturnTypeElement_H_
#define _ALITTLE_ALittleScriptGenericFunctorReturnTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptGenericFunctorReturnOneTypeElement;
class ALittleScriptStringElement;

class ALittleScriptGenericFunctorReturnTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericFunctorReturnTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericFunctorReturnTypeElement() { }

private:
    bool m_flag_GenericFunctorReturnOneType = false;
    std::vector<std::shared_ptr<ALittleScriptGenericFunctorReturnOneTypeElement>> m_list_GenericFunctorReturnOneType;
public:
    const std::vector<std::shared_ptr<ALittleScriptGenericFunctorReturnOneTypeElement>>& GetGenericFunctorReturnOneTypeList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptGenericFunctorReturnTypeElement_H_
