#ifndef _ALITTLE_ALittleScriptGenericFunctorParamTypeElement_H_
#define _ALITTLE_ALittleScriptGenericFunctorParamTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptGenericFunctorParamOneTypeElement;
class ALittleScriptStringElement;

class ALittleScriptGenericFunctorParamTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericFunctorParamTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericFunctorParamTypeElement() { }

private:
    bool m_flag_GenericFunctorParamOneType = false;
    std::vector<std::shared_ptr<ALittleScriptGenericFunctorParamOneTypeElement>> m_list_GenericFunctorParamOneType;
public:
    const std::vector<std::shared_ptr<ALittleScriptGenericFunctorParamOneTypeElement>>& GetGenericFunctorParamOneTypeList()
    {
        if (m_flag_GenericFunctorParamOneType) return m_list_GenericFunctorParamOneType;
        m_flag_GenericFunctorParamOneType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorParamOneTypeElement>(child);
            if (node != nullptr)
                m_list_GenericFunctorParamOneType.push_back(node);
        }
        return m_list_GenericFunctorParamOneType;
    }
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList()
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

#endif // _ALITTLE_ALittleScriptGenericFunctorParamTypeElement_H_
