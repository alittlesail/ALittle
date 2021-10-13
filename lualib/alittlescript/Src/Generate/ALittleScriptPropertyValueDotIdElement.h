#ifndef _ALITTLE_ALittleScriptPropertyValueDotIdElement_H_
#define _ALITTLE_ALittleScriptPropertyValueDotIdElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueDotIdNameElement;
class ALittleScriptStringElement;

class ALittleScriptPropertyValueDotIdElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueDotIdElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueDotIdElement() { }

private:
    bool m_flag_PropertyValueDotIdName = false;
    std::shared_ptr<ALittleScriptPropertyValueDotIdNameElement> m_cache_PropertyValueDotIdName;
public:
    std::shared_ptr<ALittleScriptPropertyValueDotIdNameElement> GetPropertyValueDotIdName();
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptPropertyValueDotIdElement_H_
