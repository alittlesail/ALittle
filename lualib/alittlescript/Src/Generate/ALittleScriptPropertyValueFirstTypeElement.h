#ifndef _ALITTLE_ALittleScriptPropertyValueFirstTypeElement_H_
#define _ALITTLE_ALittleScriptPropertyValueFirstTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueThisTypeElement;
class ALittleScriptPropertyValueCustomTypeElement;
class ALittleScriptPropertyValueCastTypeElement;

class ALittleScriptPropertyValueFirstTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueFirstTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueFirstTypeElement() { }

private:
    bool m_flag_PropertyValueThisType = false;
    std::shared_ptr<ALittleScriptPropertyValueThisTypeElement> m_cache_PropertyValueThisType;
public:
    std::shared_ptr<ALittleScriptPropertyValueThisTypeElement> GetPropertyValueThisType();
private:
    bool m_flag_PropertyValueCustomType = false;
    std::shared_ptr<ALittleScriptPropertyValueCustomTypeElement> m_cache_PropertyValueCustomType;
public:
    std::shared_ptr<ALittleScriptPropertyValueCustomTypeElement> GetPropertyValueCustomType();
private:
    bool m_flag_PropertyValueCastType = false;
    std::shared_ptr<ALittleScriptPropertyValueCastTypeElement> m_cache_PropertyValueCastType;
public:
    std::shared_ptr<ALittleScriptPropertyValueCastTypeElement> GetPropertyValueCastType();
};

#endif // _ALITTLE_ALittleScriptPropertyValueFirstTypeElement_H_
