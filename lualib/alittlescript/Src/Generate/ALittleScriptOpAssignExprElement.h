#ifndef _ALITTLE_ALittleScriptOpAssignExprElement_H_
#define _ALITTLE_ALittleScriptOpAssignExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueElement;
class ALittleScriptOpAssignElement;
class ALittleScriptValueStatElement;
class ALittleScriptStringElement;

class ALittleScriptOpAssignExprElement : public ABnfNodeElement
{
public:
    ALittleScriptOpAssignExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOpAssignExprElement() { }

private:
    bool m_flag_PropertyValue = false;
    std::vector<std::shared_ptr<ALittleScriptPropertyValueElement>> m_list_PropertyValue;
public:
    const std::vector<std::shared_ptr<ALittleScriptPropertyValueElement>>& GetPropertyValueList();
private:
    bool m_flag_OpAssign = false;
    std::shared_ptr<ALittleScriptOpAssignElement> m_cache_OpAssign;
public:
    std::shared_ptr<ALittleScriptOpAssignElement> GetOpAssign();
private:
    bool m_flag_ValueStat = false;
    std::shared_ptr<ALittleScriptValueStatElement> m_cache_ValueStat;
public:
    std::shared_ptr<ALittleScriptValueStatElement> GetValueStat();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptOpAssignExprElement_H_
