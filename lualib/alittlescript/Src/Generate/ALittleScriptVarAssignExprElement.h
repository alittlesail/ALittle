#ifndef _ALITTLE_ALittleScriptVarAssignExprElement_H_
#define _ALITTLE_ALittleScriptVarAssignExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptVarAssignDecElement;
class ALittleScriptValueStatElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptVarAssignExprElement : public ABnfNodeElement
{
public:
    ALittleScriptVarAssignExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptVarAssignExprElement() { }

private:
    bool m_flag_VarAssignDec = false;
    std::vector<std::shared_ptr<ALittleScriptVarAssignDecElement>> m_list_VarAssignDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptVarAssignDecElement>>& GetVarAssignDecList();
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

#endif // _ALITTLE_ALittleScriptVarAssignExprElement_H_
