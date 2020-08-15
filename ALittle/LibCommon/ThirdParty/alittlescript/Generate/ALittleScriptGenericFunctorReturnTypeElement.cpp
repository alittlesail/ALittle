#include "ALittleScriptGenericFunctorReturnTypeElement.h"

#include "ALittleScriptGenericFunctorReturnOneTypeElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptGenericFunctorReturnOneTypeElement>>& ALittleScriptGenericFunctorReturnTypeElement::GetGenericFunctorReturnOneTypeList()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptGenericFunctorReturnTypeElement::GetStringList()
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

