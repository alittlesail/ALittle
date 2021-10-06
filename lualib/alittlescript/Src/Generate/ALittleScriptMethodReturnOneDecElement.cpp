#include "ALittleScriptMethodReturnOneDecElement.h"

#include "ALittleScriptMethodReturnTailDecElement.h"
#include "ALittleScriptAllTypeElement.h"

std::shared_ptr<ALittleScriptMethodReturnTailDecElement> ALittleScriptMethodReturnOneDecElement::GetMethodReturnTailDec()
{
    if (m_flag_MethodReturnTailDec) return m_cache_MethodReturnTailDec;
    m_flag_MethodReturnTailDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodReturnTailDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodReturnTailDec = node;
            break;
        }
    }
    return m_cache_MethodReturnTailDec;
}
std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptMethodReturnOneDecElement::GetAllType()
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

