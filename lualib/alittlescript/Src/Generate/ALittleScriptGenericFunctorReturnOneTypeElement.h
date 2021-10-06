#ifndef _ALITTLE_ALittleScriptGenericFunctorReturnOneTypeElement_H_
#define _ALITTLE_ALittleScriptGenericFunctorReturnOneTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

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
    std::shared_ptr<ALittleScriptGenericFunctorReturnTailElement> GetGenericFunctorReturnTail();
private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType();
};

#endif // _ALITTLE_ALittleScriptGenericFunctorReturnOneTypeElement_H_
