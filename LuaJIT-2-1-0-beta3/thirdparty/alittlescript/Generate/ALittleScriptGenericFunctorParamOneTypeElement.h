#ifndef _ALITTLE_ALittleScriptGenericFunctorParamOneTypeElement_H_
#define _ALITTLE_ALittleScriptGenericFunctorParamOneTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeElement;
class ALittleScriptGenericFunctorParamTailElement;

class ALittleScriptGenericFunctorParamOneTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericFunctorParamOneTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericFunctorParamOneTypeElement() { }

private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType();
private:
    bool m_flag_GenericFunctorParamTail = false;
    std::shared_ptr<ALittleScriptGenericFunctorParamTailElement> m_cache_GenericFunctorParamTail;
public:
    std::shared_ptr<ALittleScriptGenericFunctorParamTailElement> GetGenericFunctorParamTail();
};

#endif // _ALITTLE_ALittleScriptGenericFunctorParamOneTypeElement_H_
