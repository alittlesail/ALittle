#ifndef _ALITTLE_ALittleScriptElseIfExprElement_H_
#define _ALITTLE_ALittleScriptElseIfExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptElseIfConditionElement;
class ALittleScriptElseIfBodyElement;
class ALittleScriptAllExprElement;
class ALittleScriptKeyElement;

class ALittleScriptElseIfExprElement : public ABnfNodeElement
{
public:
    ALittleScriptElseIfExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptElseIfExprElement() { }

private:
    bool m_flag_ElseIfCondition = false;
    std::shared_ptr<ALittleScriptElseIfConditionElement> m_cache_ElseIfCondition;
public:
    std::shared_ptr<ALittleScriptElseIfConditionElement> GetElseIfCondition()
    {
        if (m_flag_ElseIfCondition) return m_cache_ElseIfCondition;
        m_flag_ElseIfCondition = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptElseIfConditionElement>(child);
            if (node != nullptr)
            {
                m_cache_ElseIfCondition = node;
                break;
            }
        }
        return m_cache_ElseIfCondition;
    }
private:
    bool m_flag_ElseIfBody = false;
    std::shared_ptr<ALittleScriptElseIfBodyElement> m_cache_ElseIfBody;
public:
    std::shared_ptr<ALittleScriptElseIfBodyElement> GetElseIfBody()
    {
        if (m_flag_ElseIfBody) return m_cache_ElseIfBody;
        m_flag_ElseIfBody = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptElseIfBodyElement>(child);
            if (node != nullptr)
            {
                m_cache_ElseIfBody = node;
                break;
            }
        }
        return m_cache_ElseIfBody;
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

#endif // _ALITTLE_ALittleScriptElseIfExprElement_H_
