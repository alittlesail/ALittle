#include "ALittleScriptOp12Element.h"

#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptStringElement> ALittleScriptOp12Element::GetString()
{
    if (m_flag_String) return m_cache_String;
    m_flag_String = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
        if (node != nullptr)
        {
            m_cache_String = node;
            break;
        }
    }
    return m_cache_String;
}

