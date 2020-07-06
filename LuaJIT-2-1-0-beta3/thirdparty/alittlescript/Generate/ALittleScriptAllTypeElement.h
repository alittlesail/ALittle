#ifndef _ALITTLE_ALittleScriptAllTypeElement_H_
#define _ALITTLE_ALittleScriptAllTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeConstElement;
class ALittleScriptPrimitiveTypeElement;
class ALittleScriptCustomTypeElement;
class ALittleScriptGenericTypeElement;

class ALittleScriptAllTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptAllTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptAllTypeElement() { }

private:
    bool m_flag_AllTypeConst = false;
    std::shared_ptr<ALittleScriptAllTypeConstElement> m_cache_AllTypeConst;
public:
    std::shared_ptr<ALittleScriptAllTypeConstElement> GetAllTypeConst();
private:
    bool m_flag_PrimitiveType = false;
    std::shared_ptr<ALittleScriptPrimitiveTypeElement> m_cache_PrimitiveType;
public:
    std::shared_ptr<ALittleScriptPrimitiveTypeElement> GetPrimitiveType();
private:
    bool m_flag_CustomType = false;
    std::shared_ptr<ALittleScriptCustomTypeElement> m_cache_CustomType;
public:
    std::shared_ptr<ALittleScriptCustomTypeElement> GetCustomType();
private:
    bool m_flag_GenericType = false;
    std::shared_ptr<ALittleScriptGenericTypeElement> m_cache_GenericType;
public:
    std::shared_ptr<ALittleScriptGenericTypeElement> GetGenericType();
};

#endif // _ALITTLE_ALittleScriptAllTypeElement_H_
