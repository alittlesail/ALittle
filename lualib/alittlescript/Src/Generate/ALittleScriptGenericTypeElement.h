#ifndef _ALITTLE_ALittleScriptGenericTypeElement_H_
#define _ALITTLE_ALittleScriptGenericTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptGenericListTypeElement;
class ALittleScriptGenericMapTypeElement;
class ALittleScriptGenericFunctorTypeElement;

class ALittleScriptGenericTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericTypeElement() { }

private:
    bool m_flag_GenericListType = false;
    std::shared_ptr<ALittleScriptGenericListTypeElement> m_cache_GenericListType;
public:
    std::shared_ptr<ALittleScriptGenericListTypeElement> GetGenericListType();
private:
    bool m_flag_GenericMapType = false;
    std::shared_ptr<ALittleScriptGenericMapTypeElement> m_cache_GenericMapType;
public:
    std::shared_ptr<ALittleScriptGenericMapTypeElement> GetGenericMapType();
private:
    bool m_flag_GenericFunctorType = false;
    std::shared_ptr<ALittleScriptGenericFunctorTypeElement> m_cache_GenericFunctorType;
public:
    std::shared_ptr<ALittleScriptGenericFunctorTypeElement> GetGenericFunctorType();
};

#endif // _ALITTLE_ALittleScriptGenericTypeElement_H_
