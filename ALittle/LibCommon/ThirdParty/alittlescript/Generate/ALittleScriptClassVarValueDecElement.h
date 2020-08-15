#ifndef _ALITTLE_ALittleScriptClassVarValueDecElement_H_
#define _ALITTLE_ALittleScriptClassVarValueDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptConstValueElement;
class ALittleScriptOpNewStatElement;
class ALittleScriptStringElement;

class ALittleScriptClassVarValueDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassVarValueDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassVarValueDecElement() { }

private:
    bool m_flag_ConstValue = false;
    std::shared_ptr<ALittleScriptConstValueElement> m_cache_ConstValue;
public:
    std::shared_ptr<ALittleScriptConstValueElement> GetConstValue();
private:
    bool m_flag_OpNewStat = false;
    std::shared_ptr<ALittleScriptOpNewStatElement> m_cache_OpNewStat;
public:
    std::shared_ptr<ALittleScriptOpNewStatElement> GetOpNewStat();
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptClassVarValueDecElement_H_
