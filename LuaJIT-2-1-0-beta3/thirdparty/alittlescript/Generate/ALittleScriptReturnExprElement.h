#ifndef _ALITTLE_ALittleScriptReturnExprElement_H_
#define _ALITTLE_ALittleScriptReturnExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptValueStatElement;
class ALittleScriptReturnYieldElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptReturnExprElement : public ABnfNodeElement
{
public:
    ALittleScriptReturnExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptReturnExprElement() { }

private:
    bool m_flag_ValueStat = false;
    std::vector<std::shared_ptr<ALittleScriptValueStatElement>> m_list_ValueStat;
public:
    const std::vector<std::shared_ptr<ALittleScriptValueStatElement>>& GetValueStatList()
    {
        if (m_flag_ValueStat) return m_list_ValueStat;
        m_flag_ValueStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
            if (node != nullptr)
                m_list_ValueStat.push_back(node);
        }
        return m_list_ValueStat;
    }
private:
    bool m_flag_ReturnYield = false;
    std::shared_ptr<ALittleScriptReturnYieldElement> m_cache_ReturnYield;
public:
    std::shared_ptr<ALittleScriptReturnYieldElement> GetReturnYield()
    {
        if (m_flag_ReturnYield) return m_cache_ReturnYield;
        m_flag_ReturnYield = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptReturnYieldElement>(child);
            if (node != nullptr)
            {
                m_cache_ReturnYield = node;
                break;
            }
        }
        return m_cache_ReturnYield;
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
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList()
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

#endif // _ALITTLE_ALittleScriptReturnExprElement_H_
