#ifndef _ALITTLE_ALittleScriptGenericFunctorTypeElement_H_
#define _ALITTLE_ALittleScriptGenericFunctorTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptGenericFunctorReturnTypeElement;
class ALittleScriptAllTypeConstElement;
class ALittleScriptCoroutineModifierElement;
class ALittleScriptGenericFunctorParamTypeElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptGenericFunctorTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericFunctorTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericFunctorTypeElement() { }

private:
    bool m_flag_GenericFunctorReturnType = false;
    std::shared_ptr<ALittleScriptGenericFunctorReturnTypeElement> m_cache_GenericFunctorReturnType;
public:
    std::shared_ptr<ALittleScriptGenericFunctorReturnTypeElement> GetGenericFunctorReturnType();
private:
    bool m_flag_AllTypeConst = false;
    std::shared_ptr<ALittleScriptAllTypeConstElement> m_cache_AllTypeConst;
public:
    std::shared_ptr<ALittleScriptAllTypeConstElement> GetAllTypeConst();
private:
    bool m_flag_CoroutineModifier = false;
    std::shared_ptr<ALittleScriptCoroutineModifierElement> m_cache_CoroutineModifier;
public:
    std::shared_ptr<ALittleScriptCoroutineModifierElement> GetCoroutineModifier();
private:
    bool m_flag_GenericFunctorParamType = false;
    std::shared_ptr<ALittleScriptGenericFunctorParamTypeElement> m_cache_GenericFunctorParamType;
public:
    std::shared_ptr<ALittleScriptGenericFunctorParamTypeElement> GetGenericFunctorParamType();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptGenericFunctorTypeElement_H_
