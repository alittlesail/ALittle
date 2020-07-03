#ifndef _ALITTLE_ALittleScriptGenericFunctorReturnOneTypeElement_H_
#define _ALITTLE_ALittleScriptGenericFunctorReturnOneTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptGenericFunctorReturnTailElement;
class ALittleScriptAllTypeElement;

class ALittleScriptGenericFunctorReturnOneTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericFunctorReturnOneTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericFunctorReturnOneTypeElement() { }

private:
    bool m_flag_GenericFunctorReturnTail = false;
    std::shared_ptr<ALittleScriptGenericFunctorReturnTailElement> m_cache_GenericFunctorReturnTail;
public:
    std::shared_ptr<ALittleScriptGenericFunctorReturnTailElement> GetGenericFunctorReturnTail()
    {
        if (m_flag_GenericFunctorReturnTail) return m_cache_GenericFunctorReturnTail;
        m_flag_GenericFunctorReturnTail = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorReturnTailElement>(child);
            if (node != nullptr)
            {
                m_cache_GenericFunctorReturnTail = node;
                break;
            }
        }
        return m_cache_GenericFunctorReturnTail;
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

#endif // _ALITTLE_ALittleScriptGenericFunctorReturnOneTypeElement_H_
