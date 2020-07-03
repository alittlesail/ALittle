#ifndef _ALITTLE_ALittleScriptForExprElement_H_
#define _ALITTLE_ALittleScriptForExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptForConditionElement;
class ALittleScriptForBodyElement;
class ALittleScriptAllExprElement;
class ALittleScriptKeyElement;

class ALittleScriptForExprElement : public ABnfNodeElement
{
public:
    ALittleScriptForExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForExprElement() { }

private:
    bool m_flag_ForCondition = false;
    std::shared_ptr<ALittleScriptForConditionElement> m_cache_ForCondition;
public:
    std::shared_ptr<ALittleScriptForConditionElement> GetForCondition()
    {
        if (m_flag_ForCondition) return m_cache_ForCondition;
        m_flag_ForCondition = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptForConditionElement>(child);
            if (node != nullptr)
            {
                m_cache_ForCondition = node;
                break;
            }
        }
        return m_cache_ForCondition;
    }
private:
    bool m_flag_ForBody = false;
    std::shared_ptr<ALittleScriptForBodyElement> m_cache_ForBody;
public:
    std::shared_ptr<ALittleScriptForBodyElement> GetForBody()
    {
        if (m_flag_ForBody) return m_cache_ForBody;
        m_flag_ForBody = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptForBodyElement>(child);
            if (node != nullptr)
            {
                m_cache_ForBody = node;
                break;
            }
        }
        return m_cache_ForBody;
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

#endif // _ALITTLE_ALittleScriptForExprElement_H_
