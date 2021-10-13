#include "ALittleScriptGenericMapTypeElement.h"

#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptAllTypeElement>>& ALittleScriptGenericMapTypeElement::GetAllTypeList()
{
    if (m_flag_AllType) return m_list_AllType;
    m_flag_AllType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptAllTypeElement>(child);
        if (node != nullptr)
            m_list_AllType.push_back(node);
    }
    return m_list_AllType;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptGenericMapTypeElement::GetKey()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptGenericMapTypeElement::GetStringList()
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

