#ifndef _ALITTLE_ALittleScriptWhileExprElement_H_
#define _ALITTLE_ALittleScriptWhileExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptWhileConditionElement;
class ALittleScriptAllExprElement;
class ALittleScriptWhileBodyElement;
class ALittleScriptKeyElement;

class ALittleScriptWhileExprElement : public ABnfNodeElement
{
public:
    ALittleScriptWhileExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptWhileExprElement() { }

private:
    bool m_flag_WhileCondition = false;
    std::shared_ptr<ALittleScriptWhileConditionElement> m_cache_WhileCondition;
public:
    std::shared_ptr<ALittleScriptWhileConditionElement> GetWhileCondition()
    {
        if (m_flag_WhileCondition) return m_cache_WhileCondition;
        m_flag_WhileCondition = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptWhileConditionElement>(child);
            if (node != nullptr)
            {
                m_cache_WhileCondition = node;
                break;
            }
        }
        return m_cache_WhileCondition;
    }
private:
    bool m_flag_AllExpr = false;
    std::shared_ptr<ALittleScriptAllExprElement> m_cache_AllExpr;
public:
    std::shared_ptr<ALittleScriptAllExprElement> GetAllExpr()
    {
        if (m_flag_AllExpr) return m_cache_AllExpr;
        m_flag_AllExpr = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptAllExprElement>(child);
            if (node != nullptr)
            {
                m_cache_AllExpr = node;
                break;
            }
        }
        return m_cache_AllExpr;
    }
private:
    bool m_flag_WhileBody = false;
    std::shared_ptr<ALittleScriptWhileBodyElement> m_cache_WhileBody;
public:
    std::shared_ptr<ALittleScriptWhileBodyElement> GetWhileBody()
    {
        if (m_flag_WhileBody) return m_cache_WhileBody;
        m_flag_WhileBody = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptWhileBodyElement>(child);
            if (node != nullptr)
            {
                m_cache_WhileBody = node;
                break;
            }
        }
        return m_cache_WhileBody;
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
};

#endif // _ALITTLE_ALittleScriptWhileExprElement_H_
