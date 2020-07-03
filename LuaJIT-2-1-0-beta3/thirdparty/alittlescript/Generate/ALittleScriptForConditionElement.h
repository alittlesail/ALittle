#ifndef _ALITTLE_ALittleScriptForConditionElement_H_
#define _ALITTLE_ALittleScriptForConditionElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptForPairDecElement;
class ALittleScriptForStepConditionElement;
class ALittleScriptForInConditionElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptForConditionElement : public ABnfNodeElement
{
public:
    ALittleScriptForConditionElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForConditionElement() { }

private:
    bool m_flag_ForPairDec = false;
    std::shared_ptr<ALittleScriptForPairDecElement> m_cache_ForPairDec;
public:
    std::shared_ptr<ALittleScriptForPairDecElement> GetForPairDec()
    {
        if (m_flag_ForPairDec) return m_cache_ForPairDec;
        m_flag_ForPairDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptForPairDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ForPairDec = node;
                break;
            }
        }
        return m_cache_ForPairDec;
    }
private:
    bool m_flag_ForStepCondition = false;
    std::shared_ptr<ALittleScriptForStepConditionElement> m_cache_ForStepCondition;
public:
    std::shared_ptr<ALittleScriptForStepConditionElement> GetForStepCondition()
    {
        if (m_flag_ForStepCondition) return m_cache_ForStepCondition;
        m_flag_ForStepCondition = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptForStepConditionElement>(child);
            if (node != nullptr)
            {
                m_cache_ForStepCondition = node;
                break;
            }
        }
        return m_cache_ForStepCondition;
    }
private:
    bool m_flag_ForInCondition = false;
    std::shared_ptr<ALittleScriptForInConditionElement> m_cache_ForInCondition;
public:
    std::shared_ptr<ALittleScriptForInConditionElement> GetForInCondition()
    {
        if (m_flag_ForInCondition) return m_cache_ForInCondition;
        m_flag_ForInCondition = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptForInConditionElement>(child);
            if (node != nullptr)
            {
                m_cache_ForInCondition = node;
                break;
            }
        }
        return m_cache_ForInCondition;
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

#endif // _ALITTLE_ALittleScriptForConditionElement_H_
