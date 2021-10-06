#ifndef _ALITTLE_ALittleScriptGenericFunctorReturnTailElement_H_
#define _ALITTLE_ALittleScriptGenericFunctorReturnTailElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptStringElement;

class ALittleScriptGenericFunctorReturnTailElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericFunctorReturnTailElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericFunctorReturnTailElement() { }

private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptGenericFunctorReturnTailElement_H_
