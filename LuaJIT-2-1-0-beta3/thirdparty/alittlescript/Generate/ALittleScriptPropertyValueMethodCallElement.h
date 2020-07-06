#ifndef _ALITTLE_ALittleScriptPropertyValueMethodCallElement_H_
#define _ALITTLE_ALittleScriptPropertyValueMethodCallElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueMethodTemplateElement;
class ALittleScriptValueStatElement;
class ALittleScriptStringElement;

class ALittleScriptPropertyValueMethodCallElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueMethodCallElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueMethodCallElement() { }

private:
    bool m_flag_PropertyValueMethodTemplate = false;
    std::shared_ptr<ALittleScriptPropertyValueMethodTemplateElement> m_cache_PropertyValueMethodTemplate;
public:
    std::shared_ptr<ALittleScriptPropertyValueMethodTemplateElement> GetPropertyValueMethodTemplate();
private:
    bool m_flag_ValueStat = false;
    std::vector<std::shared_ptr<ALittleScriptValueStatElement>> m_list_ValueStat;
public:
    const std::vector<std::shared_ptr<ALittleScriptValueStatElement>>& GetValueStatList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptPropertyValueMethodCallElement_H_
