#ifndef _ALITTLE_ALittleScriptPropertyValueElement_H_
#define _ALITTLE_ALittleScriptPropertyValueElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueFirstTypeElement;
class ALittleScriptPropertyValueSuffixElement;

class ALittleScriptPropertyValueElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueElement() { }

private:
    bool m_flag_PropertyValueFirstType = false;
    std::shared_ptr<ALittleScriptPropertyValueFirstTypeElement> m_cache_PropertyValueFirstType;
public:
    std::shared_ptr<ALittleScriptPropertyValueFirstTypeElement> GetPropertyValueFirstType();
private:
    bool m_flag_PropertyValueSuffix = false;
    std::vector<std::shared_ptr<ALittleScriptPropertyValueSuffixElement>> m_list_PropertyValueSuffix;
public:
    const std::vector<std::shared_ptr<ALittleScriptPropertyValueSuffixElement>>& GetPropertyValueSuffixList();
};

#endif // _ALITTLE_ALittleScriptPropertyValueElement_H_
