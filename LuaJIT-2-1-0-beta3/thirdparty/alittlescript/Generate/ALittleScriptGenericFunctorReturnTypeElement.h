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
    std::vector<std::shared_ptr<ALittleScriptGenericFunctorReturnOneTypeElement>> GetGenericFunctorReturnOneTypeList()
    {
        if (m_flag_GenericFunctorReturnOneType) return m_list_GenericFunctorReturnOneType;
        m_flag_GenericFunctorReturnOneType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorReturnOneTypeElement>(child);
            if (node != nullptr)
                m_list_GenericFunctorReturnOneType.push_back(node);
        }
        return m_list_GenericFunctorReturnOneType;
    }
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    std::vector<std::shared_ptr<ALittleScriptStringElement>> GetStringList()
    {
        if (m_flag_String) return m_list_String;
        m_flag_String = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
            if (node != nullptr)
                m_list_String.push_back(node);
        }
        return m_list_String;
    }
};

#endif // _ALITTLE_ALittleScriptGenericFunctorReturnTypeElement_H_
