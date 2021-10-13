#include "ALittleScriptNumberElement.h"

#include "ALittleScriptRegexElement.h"

std::shared_ptr<ALittleScriptRegexElement> ALittleScriptNumberElement::GetRegex()
{
    if (m_flag_Regex) return m_cache_Regex;
    m_flag_Regex = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptRegexElement>(child);
        if (node != nullptr)
        {
            m_cache_Regex = node;
            break;
        }
    }
    return m_cache_Regex;
}

