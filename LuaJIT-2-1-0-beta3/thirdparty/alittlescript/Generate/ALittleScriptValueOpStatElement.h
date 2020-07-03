#ifndef _ALITTLE_ALittleScriptValueOpStatElement_H_
#define _ALITTLE_ALittleScriptValueOpStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptValueFactorStatElement;
class ALittleScriptOp5StatElement;
class ALittleScriptOp3StatElement;
class ALittleScriptOp4StatElement;
class ALittleScriptOp6StatElement;
class ALittleScriptOp7StatElement;
class ALittleScriptOp8StatElement;

class ALittleScriptValueOpStatElement : public ABnfNodeElement
{
public:
    ALittleScriptValueOpStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptValueOpStatElement() { }

private:
    bool m_flag_ValueFactorStat = false;
    std::shared_ptr<ALittleScriptValueFactorStatElement> m_cache_ValueFactorStat;
public:
    std::shared_ptr<ALittleScriptValueFactorStatElement> GetValueFactorStat()
    {
        if (m_flag_ValueFactorStat) return m_cache_ValueFactorStat;
        m_flag_ValueFactorStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptValueFactorStatElement>(child);
            if (node != nullptr)
            {
                m_cache_ValueFactorStat = node;
                break;
            }
        }
        return m_cache_ValueFactorStat;
    }
private:
    bool m_flag_Op5Stat = false;
    std::shared_ptr<ALittleScriptOp5StatElement> m_cache_Op5Stat;
public:
    std::shared_ptr<ALittleScriptOp5StatElement> GetOp5Stat()
    {
        if (m_flag_Op5Stat) return m_cache_Op5Stat;
        m_flag_Op5Stat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp5StatElement>(child);
            if (node != nullptr)
            {
                m_cache_Op5Stat = node;
                break;
            }
        }
        return m_cache_Op5Stat;
    }
private:
    bool m_flag_Op3Stat = false;
    std::shared_ptr<ALittleScriptOp3StatElement> m_cache_Op3Stat;
public:
    std::shared_ptr<ALittleScriptOp3StatElement> GetOp3Stat()
    {
        if (m_flag_Op3Stat) return m_cache_Op3Stat;
        m_flag_Op3Stat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp3StatElement>(child);
            if (node != nullptr)
            {
                m_cache_Op3Stat = node;
                break;
            }
        }
        return m_cache_Op3Stat;
    }
private:
    bool m_flag_Op4Stat = false;
    std::shared_ptr<ALittleScriptOp4StatElement> m_cache_Op4Stat;
public:
    std::shared_ptr<ALittleScriptOp4StatElement> GetOp4Stat()
    {
        if (m_flag_Op4Stat) return m_cache_Op4Stat;
        m_flag_Op4Stat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp4StatElement>(child);
            if (node != nullptr)
            {
                m_cache_Op4Stat = node;
                break;
            }
        }
        return m_cache_Op4Stat;
    }
private:
    bool m_flag_Op6Stat = false;
    std::shared_ptr<ALittleScriptOp6StatElement> m_cache_Op6Stat;
public:
    std::shared_ptr<ALittleScriptOp6StatElement> GetOp6Stat()
    {
        if (m_flag_Op6Stat) return m_cache_Op6Stat;
        m_flag_Op6Stat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp6StatElement>(child);
            if (node != nullptr)
            {
                m_cache_Op6Stat = node;
                break;
            }
        }
        return m_cache_Op6Stat;
    }
private:
    bool m_flag_Op7Stat = false;
    std::shared_ptr<ALittleScriptOp7StatElement> m_cache_Op7Stat;
public:
    std::shared_ptr<ALittleScriptOp7StatElement> GetOp7Stat()
    {
        if (m_flag_Op7Stat) return m_cache_Op7Stat;
        m_flag_Op7Stat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp7StatElement>(child);
            if (node != nullptr)
            {
                m_cache_Op7Stat = node;
                break;
            }
        }
        return m_cache_Op7Stat;
    }
private:
    bool m_flag_Op8Stat = false;
    std::shared_ptr<ALittleScriptOp8StatElement> m_cache_Op8Stat;
public:
    std::shared_ptr<ALittleScriptOp8StatElement> GetOp8Stat()
    {
        if (m_flag_Op8Stat) return m_cache_Op8Stat;
        m_flag_Op8Stat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp8StatElement>(child);
            if (node != nullptr)
            {
                m_cache_Op8Stat = node;
                break;
            }
        }
        return m_cache_Op8Stat;
    }
};

#endif // _ALITTLE_ALittleScriptValueOpStatElement_H_
