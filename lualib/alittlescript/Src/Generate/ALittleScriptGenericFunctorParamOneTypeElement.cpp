#include "ALittleScriptGenericFunctorParamOneTypeElement.h"

#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptGenericFunctorParamTailElement.h"

std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptGenericFunctorParamOneTypeElement::GetAllType()
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
std::shared_ptr<ALittleScriptGenericFunctorParamTailElement> ALittleScriptGenericFunctorParamOneTypeElement::GetGenericFunctorParamTail()
{
    if (m_flag_GenericFunctorParamTail) return m_cache_GenericFunctorParamTail;
    m_flag_GenericFunctorParamTail = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorParamTailElement>(child);
        if (node != nullptr)
        {
            m_cache_GenericFunctorParamTail = node;
            break;
        }
    }
    return m_cache_GenericFunctorParamTail;
}

