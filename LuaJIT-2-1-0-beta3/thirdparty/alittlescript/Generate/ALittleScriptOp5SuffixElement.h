#ifndef _ALITTLE_ALittleScriptOp5SuffixElement_H_
#define _ALITTLE_ALittleScriptOp5SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp5Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp5SuffixEeElement;

class ALittleScriptOp5SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp5SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp5SuffixElement() { }

private:
    bool m_flag_Op5 = false;
    std::shared_ptr<ALittleScriptOp5Element> m_cache_Op5;
public:
    std::shared_ptr<ALittleScriptOp5Element> GetOp5();
private:
    bool m_flag_ValueFactorStat = false;
    std::shared_ptr<ALittleScriptValueFactorStatElement> m_cache_ValueFactorStat;
public:
    std::shared_ptr<ALittleScriptValueFactorStatElement> GetValueFactorStat();
private:
    bool m_flag_Op2Value = false;
    std::shared_ptr<ALittleScriptOp2ValueElement> m_cache_Op2Value;
public:
    std::shared_ptr<ALittleScriptOp2ValueElement> GetOp2Value();
private:
    bool m_flag_Op5SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp5SuffixEeElement>> m_list_Op5SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp5SuffixEeElement>>& GetOp5SuffixEeList();
};

#endif // _ALITTLE_ALittleScriptOp5SuffixElement_H_
