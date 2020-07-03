#ifndef _ALITTLE_ALittleScriptMethodReturnOneDecElement_H_
#define _ALITTLE_ALittleScriptMethodReturnOneDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodReturnTailDecElement;
class ALittleScriptAllTypeElement;

class ALittleScriptMethodReturnOneDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodReturnOneDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodReturnOneDecElement() { }

private:
    bool m_flag_MethodReturnTailDec = false;
    std::shared_ptr<ALittleScriptMethodReturnTailDecElement> m_cache_MethodReturnTailDec;
public:
    std::shared_ptr<ALittleScriptMethodReturnTailDecElement> GetMethodReturnTailDec()
    {
        if (m_flag_MethodReturnTailDec) return m_cache_MethodReturnTailDec;
        m_flag_MethodReturnTailDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodReturnTailDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodReturnTailDec = node;
                break;
            }
        }
        return m_cache_MethodReturnTailDec;
    }
private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType()
    {
        if (m_flag_AllType) return m_cache_AllType;
        m_flag_AllType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptAllTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_AllType = node;
                break;
            }
        }
        return m_cache_AllType;
    }
};

#endif // _ALITTLE_ALittleScriptMethodReturnOneDecElement_H_
