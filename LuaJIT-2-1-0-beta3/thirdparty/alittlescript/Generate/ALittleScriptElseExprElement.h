#ifndef _ALITTLE_ALittleScriptElseExprElement_H_
#define _ALITTLE_ALittleScriptElseExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptElseBodyElement;
class ALittleScriptAllExprElement;
class ALittleScriptKeyElement;

class ALittleScriptElseExprElement : public ABnfNodeElement
{
public:
    ALittleScriptElseExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptElseExprElement() { }

private:
    bool m_flag_ElseBody = false;
    std::shared_ptr<ALittleScriptElseBodyElement> m_cache_ElseBody;
public:
    std::shared_ptr<ALittleScriptElseBodyElement> GetElseBody()
    {
        if (m_flag_ElseBody) return m_cache_ElseBody;
        m_flag_ElseBody = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptElseBodyElement>(child);
            if (node != nullptr)
            {
                m_cache_ElseBody = node;
                break;
            }
        }
        return m_cache_ElseBody;
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

#endif // _ALITTLE_ALittleScriptElseExprElement_H_
