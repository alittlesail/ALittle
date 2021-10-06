#ifndef _ALITTLE_ALittleScriptOp12SuffixElement_H_
#define _ALITTLE_ALittleScriptOp12SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp12Element;
class ALittleScriptOp2ValueElement;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp12SuffixEeElement;

class ALittleScriptOp12SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp12SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp12SuffixElement() { }

private:
    bool m_flag_Op12 = false;
    std::shared_ptr<ALittleScriptOp12Element> m_cache_Op12;
public:
    std::shared_ptr<ALittleScriptOp12Element> GetOp12();
private:
    bool m_flag_Op2Value = false;
    std::shared_ptr<ALittleScriptOp2ValueElement> m_cache_Op2Value;
public:
    std::shared_ptr<ALittleScriptOp2ValueElement> GetOp2Value();
private:
    bool m_flag_ValueFactorStat = false;
    std::shared_ptr<ALittleScriptValueFactorStatElement> m_cache_ValueFactorStat;
public:
    std::shared_ptr<ALittleScriptValueFactorStatElement> GetValueFactorStat();
private:
    bool m_flag_Op12SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp12SuffixEeElement>> m_list_Op12SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp12SuffixEeElement>>& GetOp12SuffixEeList();
};

#endif // _ALITTLE_ALittleScriptOp12SuffixElement_H_
