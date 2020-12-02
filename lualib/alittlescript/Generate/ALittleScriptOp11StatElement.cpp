#include "ALittleScriptOp11StatElement.h"

#include "ALittleScriptOp11SuffixElement.h"
#include "ALittleScriptOp11SuffixExElement.h"

std::shared_ptr<ALittleScriptOp11SuffixElement> ALittleScriptOp11StatElement::GetOp11Suffix()
{
    if (m_flag_Op11Suffix) return m_cache_Op11Suffix;
    m_flag_Op11Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp11SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op11Suffix = node;
            break;
        }
    }
    return m_cache_Op11Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp11SuffixExElement>>& ALittleScriptOp11StatElement::GetOp11SuffixExList()
{
    if (m_flag_Op11SuffixEx) return m_list_Op11SuffixEx;
    m_flag_Op11SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp11SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op11SuffixEx.push_back(node);
    }
    return m_list_Op11SuffixEx;
}

