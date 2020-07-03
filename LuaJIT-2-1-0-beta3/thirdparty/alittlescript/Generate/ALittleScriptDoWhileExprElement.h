#ifndef _ALITTLE_ALittleScriptDoWhileExprElement_H_
#define _ALITTLE_ALittleScriptDoWhileExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptDoWhileBodyElement;
class ALittleScriptDoWhileConditionElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptDoWhileExprElement : public ABnfNodeElement
{
public:
    ALittleScriptDoWhileExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptDoWhileExprElement() { }

private:
    bool m_flag_DoWhileBody = false;
    std::shared_ptr<ALittleScriptDoWhileBodyElement> m_cache_DoWhileBody;
public:
    std::shared_ptr<ALittleScriptDoWhileBodyElement> GetDoWhileBody()
    {
        if (m_flag_DoWhileBody) return m_cache_DoWhileBody;
        m_flag_DoWhileBody = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptDoWhileBodyElement>(child);
            if (node != nullptr)
            {
                m_cache_DoWhileBody = node;
                break;
            }
        }
        return m_cache_DoWhileBody;
    }
private:
    bool m_flag_DoWhileCondition = false;
    std::shared_ptr<ALittleScriptDoWhileConditionElement> m_cache_DoWhileCondition;
public:
    std::shared_ptr<ALittleScriptDoWhileConditionElement> GetDoWhileCondition()
    {
        if (m_flag_DoWhileCondition) return m_cache_DoWhileCondition;
        m_flag_DoWhileCondition = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptDoWhileConditionElement>(child);
            if (node != nullptr)
            {
                m_cache_DoWhileCondition = node;
                break;
            }
        }
        return m_cache_DoWhileCondition;
    }
private:
    bool m_flag_Key = false;
    std::vector<std::shared_ptr<ALittleScriptKeyElement>> m_list_Key;
public:
    std::vector<std::shared_ptr<ALittleScriptKeyElement>> GetKeyList()
    {
        if (m_flag_Key) return m_list_Key;
        m_flag_Key = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptKeyElement>(child);
            if (node != nullptr)
                m_list_Key.push_back(node);
        }
        return m_list_Key;
    }
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString()
    {
        if (m_flag_String) return m_cache_String;
        m_flag_String = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
            if (node != nullptr)
            {
                m_cache_String = node;
                break;
            }
        }
        return m_cache_String;
    }
};

#endif // _ALITTLE_ALittleScriptDoWhileExprElement_H_
