#ifndef _ALITTLE_ALittleScriptForInConditionElement_H_
#define _ALITTLE_ALittleScriptForInConditionElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptForPairDecElement;
class ALittleScriptValueStatElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptForInConditionElement : public ABnfNodeElement
{
public:
    ALittleScriptForInConditionElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForInConditionElement() { }

private:
    bool m_flag_ForPairDec = false;
    std::vector<std::shared_ptr<ALittleScriptForPairDecElement>> m_list_ForPairDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptForPairDecElement>>& GetForPairDecList();
private:
    bool m_flag_ValueStat = false;
    std::shared_ptr<ALittleScriptValueStatElement> m_cache_ValueStat;
public:
    std::shared_ptr<ALittleScriptValueStatElement> GetValueStat();
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

#endif // _ALITTLE_ALittleScriptForInConditionElement_H_
