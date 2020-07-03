#ifndef _ALITTLE_ALittleScriptForStepConditionElement_H_
#define _ALITTLE_ALittleScriptForStepConditionElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptForStartStatElement;
class ALittleScriptForEndStatElement;
class ALittleScriptForStepStatElement;
class ALittleScriptStringElement;

class ALittleScriptForStepConditionElement : public ABnfNodeElement
{
public:
    ALittleScriptForStepConditionElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForStepConditionElement() { }

private:
    bool m_flag_ForStartStat = false;
    std::shared_ptr<ALittleScriptForStartStatElement> m_cache_ForStartStat;
public:
    std::shared_ptr<ALittleScriptForStartStatElement> GetForStartStat()
    {
        if (m_flag_ForStartStat) return m_cache_ForStartStat;
        m_flag_ForStartStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptForStartStatElement>(child);
            if (node != nullptr)
            {
                m_cache_ForStartStat = node;
                break;
            }
        }
        return m_cache_ForStartStat;
    }
private:
    bool m_flag_ForEndStat = false;
    std::shared_ptr<ALittleScriptForEndStatElement> m_cache_ForEndStat;
public:
    std::shared_ptr<ALittleScriptForEndStatElement> GetForEndStat()
    {
        if (m_flag_ForEndStat) return m_cache_ForEndStat;
        m_flag_ForEndStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptForEndStatElement>(child);
            if (node != nullptr)
            {
                m_cache_ForEndStat = node;
                break;
            }
        }
        return m_cache_ForEndStat;
    }
private:
    bool m_flag_ForStepStat = false;
    std::shared_ptr<ALittleScriptForStepStatElement> m_cache_ForStepStat;
public:
    std::shared_ptr<ALittleScriptForStepStatElement> GetForStepStat()
    {
        if (m_flag_ForStepStat) return m_cache_ForStepStat;
        m_flag_ForStepStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptForStepStatElement>(child);
            if (node != nullptr)
            {
                m_cache_ForStepStat = node;
                break;
            }
        }
        return m_cache_ForStepStat;
    }
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    std::vector<std::shared_ptr<ALittleScriptStringElement>> GetStringList()
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
};

#endif // _ALITTLE_ALittleScriptForStepConditionElement_H_
