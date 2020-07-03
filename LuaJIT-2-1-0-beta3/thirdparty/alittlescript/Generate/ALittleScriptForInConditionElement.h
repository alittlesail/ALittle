#ifndef _ALITTLE_ALittleScriptForInConditionElement_H_
#define _ALITTLE_ALittleScriptForInConditionElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptForPairDecElement;
class ALittleScriptValueStatElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptForInConditionElement : public ABnfNodeElement
{
public:
    ALittleScriptForInConditionElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForInConditionElement() { }

private:
    bool m_flag_ForPairDec = false;
    std::vector<std::shared_ptr<ALittleScriptForPairDecElement>> m_list_ForPairDec;
public:
    std::vector<std::shared_ptr<ALittleScriptForPairDecElement>> GetForPairDecList()
    {
        if (m_flag_ForPairDec) return m_list_ForPairDec;
        m_flag_ForPairDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptForPairDecElement>(child);
            if (node != nullptr)
                m_list_ForPairDec.push_back(node);
        }
        return m_list_ForPairDec;
    }
private:
    bool m_flag_ValueStat = false;
    std::shared_ptr<ALittleScriptValueStatElement> m_cache_ValueStat;
public:
    std::shared_ptr<ALittleScriptValueStatElement> GetValueStat()
    {
        if (m_flag_ValueStat) return m_cache_ValueStat;
        m_flag_ValueStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
            if (node != nullptr)
            {
                m_cache_ValueStat = node;
                break;
            }
        }
        return m_cache_ValueStat;
    }
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey()
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

#endif // _ALITTLE_ALittleScriptForInConditionElement_H_
