#include "ALittleScriptStructOptionDecElement.h"

#include "ALittleScriptStructOptionNameDecElement.h"
#include "ALittleScriptTextElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptStructOptionNameDecElement> ALittleScriptStructOptionDecElement::GetStructOptionNameDec()
{
    if (m_flag_StructOptionNameDec) return m_cache_StructOptionNameDec;
    m_flag_StructOptionNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStructOptionNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_StructOptionNameDec = node;
            break;
        }
    }
    return m_cache_StructOptionNameDec;
}
std::shared_ptr<ALittleScriptTextElement> ALittleScriptStructOptionDecElement::GetText()
{
    if (m_flag_Text) return m_cache_Text;
    m_flag_Text = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTextElement>(child);
        if (node != nullptr)
        {
            m_cache_Text = node;
            break;
        }
    }
    return m_cache_Text;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptStructOptionDecElement::GetKey()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptStructOptionDecElement::GetStringList()
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

