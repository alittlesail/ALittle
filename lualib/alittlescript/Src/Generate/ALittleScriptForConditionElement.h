#ifndef _ALITTLE_ALittleScriptForConditionElement_H_
#define _ALITTLE_ALittleScriptForConditionElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptForPairDecElement;
class ALittleScriptForStepConditionElement;
class ALittleScriptForInConditionElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptForConditionElement : public ABnfNodeElement
{
public:
    ALittleScriptForConditionElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForConditionElement() { }

private:
    bool m_flag_ForPairDec = false;
    std::shared_ptr<ALittleScriptForPairDecElement> m_cache_ForPairDec;
public:
    std::shared_ptr<ALittleScriptForPairDecElement> GetForPairDec();
private:
    bool m_flag_ForStepCondition = false;
    std::shared_ptr<ALittleScriptForStepConditionElement> m_cache_ForStepCondition;
public:
    std::shared_ptr<ALittleScriptForStepConditionElement> GetForStepCondition();
private:
    bool m_flag_ForInCondition = false;
    std::shared_ptr<ALittleScriptForInConditionElement> m_cache_ForInCondition;
public:
    std::shared_ptr<ALittleScriptForInConditionElement> GetForInCondition();
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

#endif // _ALITTLE_ALittleScriptForConditionElement_H_
