#ifndef _ALITTLE_ALittleScriptClassCtorDecElement_H_
#define _ALITTLE_ALittleScriptClassCtorDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodParamDecElement;
class ALittleScriptMethodBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptClassCtorDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassCtorDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassCtorDecElement() { }

private:
    bool m_flag_MethodParamDec = false;
    std::shared_ptr<ALittleScriptMethodParamDecElement> m_cache_MethodParamDec;
public:
    std::shared_ptr<ALittleScriptMethodParamDecElement> GetMethodParamDec()
    {
        if (m_flag_MethodParamDec) return m_cache_MethodParamDec;
        m_flag_MethodParamDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodParamDec = node;
                break;
            }
        }
        return m_cache_MethodParamDec;
    }
private:
    bool m_flag_MethodBodyDec = false;
    std::shared_ptr<ALittleScriptMethodBodyDecElement> m_cache_MethodBodyDec;
public:
    std::shared_ptr<ALittleScriptMethodBodyDecElement> GetMethodBodyDec()
    {
        if (m_flag_MethodBodyDec) return m_cache_MethodBodyDec;
        m_flag_MethodBodyDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodBodyDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodBodyDec = node;
                break;
            }
        }
        return m_cache_MethodBodyDec;
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

#endif // _ALITTLE_ALittleScriptClassCtorDecElement_H_
