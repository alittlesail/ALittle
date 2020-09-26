#include "ALittleScriptTemplateExtendsStructDecElement.h"

#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptKeyElement> ALittleScriptTemplateExtendsStructDecElement::GetKey()
{
    if (m_flag_Key) return m_cache_Key;
    m_flag_Key = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptKeyElement>(child);
        if (node != nullptr)
        {
            m_cache_Key = node;
            break;
        }
    }
    return m_cache_Key;
}

