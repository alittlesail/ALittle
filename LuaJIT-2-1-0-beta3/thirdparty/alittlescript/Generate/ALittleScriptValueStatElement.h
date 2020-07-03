#ifndef _ALITTLE_ALittleScriptValueStatElement_H_
#define _ALITTLE_ALittleScriptValueStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOpNewListStatElement;
class ALittleScriptOpNewStatElement;
class ALittleScriptBindStatElement;
class ALittleScriptTcallStatElement;
class ALittleScriptOp2StatElement;
class ALittleScriptValueOpStatElement;

class ALittleScriptValueStatElement : public ABnfNodeElement
{
public:
    ALittleScriptValueStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptValueStatElement() { }

private:
    bool m_flag_OpNewListStat = false;
    std::shared_ptr<ALittleScriptOpNewListStatElement> m_cache_OpNewListStat;
public:
    std::shared_ptr<ALittleScriptOpNewListStatElement> GetOpNewListStat()
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
private:
    bool m_flag_OpNewStat = false;
    std::shared_ptr<ALittleScriptOpNewStatElement> m_cache_OpNewStat;
public:
    std::shared_ptr<ALittleScriptOpNewStatElement> GetOpNewStat()
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
private:
    bool m_flag_BindStat = false;
    std::shared_ptr<ALittleScriptBindStatElement> m_cache_BindStat;
public:
    std::shared_ptr<ALittleScriptBindStatElement> GetBindStat()
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
private:
    bool m_flag_TcallStat = false;
    std::shared_ptr<ALittleScriptTcallStatElement> m_cache_TcallStat;
public:
    std::shared_ptr<ALittleScriptTcallStatElement> GetTcallStat()
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
private:
    bool m_flag_Op2Stat = false;
    std::shared_ptr<ALittleScriptOp2StatElement> m_cache_Op2Stat;
public:
    std::shared_ptr<ALittleScriptOp2StatElement> GetOp2Stat()
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
private:
    bool m_flag_ValueOpStat = false;
    std::shared_ptr<ALittleScriptValueOpStatElement> m_cache_ValueOpStat;
public:
    std::shared_ptr<ALittleScriptValueOpStatElement> GetValueOpStat()
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
};

#endif // _ALITTLE_ALittleScriptValueStatElement_H_
