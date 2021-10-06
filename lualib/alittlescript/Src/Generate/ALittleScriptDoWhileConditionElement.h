#ifndef _ALITTLE_ALittleScriptDoWhileConditionElement_H_
#define _ALITTLE_ALittleScriptDoWhileConditionElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptValueStatElement;
class ALittleScriptStringElement;

class ALittleScriptDoWhileConditionElement : public ABnfNodeElement
{
public:
    ALittleScriptDoWhileConditionElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptDoWhileConditionElement() { }

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

#endif // _ALITTLE_ALittleScriptDoWhileConditionElement_H_
