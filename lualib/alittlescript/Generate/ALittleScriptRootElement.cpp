#include "ALittleScriptRootElement.h"

#include "ALittleScriptNamespaceDecElement.h"

std::shared_ptr<ALittleScriptNamespaceDecElement> ALittleScriptRootElement::GetNamespaceDec()
{
    if (m_flag_NamespaceDec) return m_cache_NamespaceDec;
    m_flag_NamespaceDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(child);
        if (node != nullptr)
        {
            m_cache_NamespaceDec = node;
            break;
        }
    }
    return m_cache_NamespaceDec;
}

