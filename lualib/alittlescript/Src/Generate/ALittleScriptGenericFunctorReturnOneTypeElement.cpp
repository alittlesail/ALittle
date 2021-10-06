#include "ALittleScriptGenericFunctorReturnOneTypeElement.h"

#include "ALittleScriptGenericFunctorReturnTailElement.h"
#include "ALittleScriptAllTypeElement.h"

std::shared_ptr<ALittleScriptGenericFunctorReturnTailElement> ALittleScriptGenericFunctorReturnOneTypeElement::GetGenericFunctorReturnTail()
{
    if (m_flag_GenericFunctorReturnTail) return m_cache_GenericFunctorReturnTail;
    m_flag_GenericFunctorReturnTail = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorReturnTailElement>(child);
        if (node != nullptr)
        {
            m_cache_GenericFunctorReturnTail = node;
            break;
        }
    }
    return m_cache_GenericFunctorReturnTail;
}
std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptGenericFunctorReturnOneTypeElement::GetAllType()
{
    if (m_flag_AllType) return m_cache_AllType;
    m_flag_AllType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptAllTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_AllType = node;
            break;
        }
    }
    return m_cache_AllType;
}

