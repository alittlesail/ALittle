#ifndef _ALITTLE_ALittleScriptOp6SuffixElement_H_
#define _ALITTLE_ALittleScriptOp6SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp6Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp6SuffixEeElement;
class ALittleScriptOp2ValueElement;

class ALittleScriptOp6SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp6SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp6SuffixElement() { }

private:
    bool m_flag_Op6 = false;
    std::shared_ptr<ALittleScriptOp6Element> m_cache_Op6;
public:
    std::shared_ptr<ALittleScriptOp6Element> GetOp6();
private:
    bool m_flag_ValueFactorStat = false;
    std::shared_ptr<ALittleScriptValueFactorStatElement> m_cache_ValueFactorStat;
public:
    std::shared_ptr<ALittleScriptValueFactorStatElement> GetValueFactorStat();
private:
    bool m_flag_Op6SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp6SuffixEeElement>> m_list_Op6SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp6SuffixEeElement>>& GetOp6SuffixEeList();
private:
    bool m_flag_Op2Value = false;
    std::shared_ptr<ALittleScriptOp2ValueElement> m_cache_Op2Value;
public:
    std::shared_ptr<ALittleScriptOp2ValueElement> GetOp2Value();
};

#endif // _ALITTLE_ALittleScriptOp6SuffixElement_H_
