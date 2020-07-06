#ifndef _ALITTLE_ALittleScriptPropertyValueSuffixElement_H_
#define _ALITTLE_ALittleScriptPropertyValueSuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueDotIdElement;
class ALittleScriptPropertyValueMethodCallElement;
class ALittleScriptPropertyValueBracketValueElement;

class ALittleScriptPropertyValueSuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueSuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueSuffixElement() { }

private:
    bool m_flag_PropertyValueDotId = false;
    std::shared_ptr<ALittleScriptPropertyValueDotIdElement> m_cache_PropertyValueDotId;
public:
    std::shared_ptr<ALittleScriptPropertyValueDotIdElement> GetPropertyValueDotId();
private:
    bool m_flag_PropertyValueMethodCall = false;
    std::shared_ptr<ALittleScriptPropertyValueMethodCallElement> m_cache_PropertyValueMethodCall;
public:
    std::shared_ptr<ALittleScriptPropertyValueMethodCallElement> GetPropertyValueMethodCall();
private:
    bool m_flag_PropertyValueBracketValue = false;
    std::shared_ptr<ALittleScriptPropertyValueBracketValueElement> m_cache_PropertyValueBracketValue;
public:
    std::shared_ptr<ALittleScriptPropertyValueBracketValueElement> GetPropertyValueBracketValue();
};

#endif // _ALITTLE_ALittleScriptPropertyValueSuffixElement_H_
