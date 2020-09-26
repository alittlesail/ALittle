#include "ALittleScriptGenericFunctorParamTypeElement.h"

#include "ALittleScriptGenericFunctorParamOneTypeElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptGenericFunctorParamOneTypeElement>>& ALittleScriptGenericFunctorParamTypeElement::GetGenericFunctorParamOneTypeList()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptGenericFunctorParamTypeElement::GetStringList()
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

