#include "ALittleScriptValueStatElement.h"

#include "ALittleScriptOpNewListStatElement.h"
#include "ALittleScriptOpNewStatElement.h"
#include "ALittleScriptBindStatElement.h"
#include "ALittleScriptTcallStatElement.h"
#include "ALittleScriptOp2StatElement.h"
#include "ALittleScriptValueOpStatElement.h"

std::shared_ptr<ALittleScriptOpNewListStatElement> ALittleScriptValueStatElement::GetOpNewListStat()
{
    if (m_flag_OpNewListStat) return m_cache_OpNewListStat;
    m_flag_OpNewListStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOpNewListStatElement>(child);
        if (node != nullptr)
        {
            m_cache_OpNewListStat = node;
            break;
        }
    }
    return m_cache_OpNewListStat;
}
std::shared_ptr<ALittleScriptOpNewStatElement> ALittleScriptValueStatElement::GetOpNewStat()
{
    if (m_flag_OpNewStat) return m_cache_OpNewStat;
    m_flag_OpNewStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(child);
        if (node != nullptr)
        {
            m_cache_OpNewStat = node;
            break;
        }
    }
    return m_cache_OpNewStat;
}
std::shared_ptr<ALittleScriptBindStatElement> ALittleScriptValueStatElement::GetBindStat()
{
    if (m_flag_BindStat) return m_cache_BindStat;
    m_flag_BindStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptBindStatElement>(child);
        if (node != nullptr)
        {
            m_cache_BindStat = node;
            break;
        }
    }
    return m_cache_BindStat;
}
std::shared_ptr<ALittleScriptTcallStatElement> ALittleScriptValueStatElement::GetTcallStat()
{
    if (m_flag_TcallStat) return m_cache_TcallStat;
    m_flag_TcallStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTcallStatElement>(child);
        if (node != nullptr)
        {
            m_cache_TcallStat = node;
            break;
        }
    }
    return m_cache_TcallStat;
}
std::shared_ptr<ALittleScriptOp2StatElement> ALittleScriptValueStatElement::GetOp2Stat()
{
    if (m_flag_Op2Stat) return m_cache_Op2Stat;
    m_flag_Op2Stat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp2StatElement>(child);
        if (node != nullptr)
        {
            m_cache_Op2Stat = node;
            break;
        }
    }
    return m_cache_Op2Stat;
}
std::shared_ptr<ALittleScriptValueOpStatElement> ALittleScriptValueStatElement::GetValueOpStat()
{
    if (m_flag_ValueOpStat) return m_cache_ValueOpStat;
    m_flag_ValueOpStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptValueOpStatElement>(child);
        if (node != nullptr)
        {
            m_cache_ValueOpStat = node;
            break;
        }
    }
    return m_cache_ValueOpStat;
}

