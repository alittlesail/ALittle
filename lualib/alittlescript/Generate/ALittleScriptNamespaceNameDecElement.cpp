#include "ALittleScriptNamespaceNameDecElement.h"

#include "ALittleScriptIdElement.h"

std::shared_ptr<ALittleScriptIdElement> ALittleScriptNamespaceNameDecElement::GetId()
{
    if (m_flag_Id) return m_cache_Id;
    m_flag_Id = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptIdElement>(child);
        if (node != nullptr)
        {
            m_cache_Id = node;
            break;
        }
    }
    return m_cache_Id;
}

