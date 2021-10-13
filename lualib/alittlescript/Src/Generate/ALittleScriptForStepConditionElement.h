#ifndef _ALITTLE_ALittleScriptForStepConditionElement_H_
#define _ALITTLE_ALittleScriptForStepConditionElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptForStartStatElement;
class ALittleScriptForEndStatElement;
class ALittleScriptForStepStatElement;
class ALittleScriptStringElement;

class ALittleScriptForStepConditionElement : public ABnfNodeElement
{
public:
    ALittleScriptForStepConditionElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForStepConditionElement() { }

private:
    bool m_flag_ForStartStat = false;
    std::shared_ptr<ALittleScriptForStartStatElement> m_cache_ForStartStat;
public:
    std::shared_ptr<ALittleScriptForStartStatElement> GetForStartStat();
private:
    bool m_flag_ForEndStat = false;
    std::shared_ptr<ALittleScriptForEndStatElement> m_cache_ForEndStat;
public:
    std::shared_ptr<ALittleScriptForEndStatElement> GetForEndStat();
private:
    bool m_flag_ForStepStat = false;
    std::shared_ptr<ALittleScriptForStepStatElement> m_cache_ForStepStat;
public:
    std::shared_ptr<ALittleScriptForStepStatElement> GetForStepStat();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptForStepConditionElement_H_
