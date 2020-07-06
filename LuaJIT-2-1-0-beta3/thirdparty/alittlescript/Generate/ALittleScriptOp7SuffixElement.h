#ifndef _ALITTLE_ALittleScriptOp7SuffixElement_H_
#define _ALITTLE_ALittleScriptOp7SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp7Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp7SuffixEeElement;

class ALittleScriptOp7SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp7SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp7SuffixElement() { }

private:
    bool m_flag_Op7 = false;
    std::shared_ptr<ALittleScriptOp7Element> m_cache_Op7;
public:
    std::shared_ptr<ALittleScriptOp7Element> GetOp7();
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
    bool m_flag_Op7SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp7SuffixEeElement>> m_list_Op7SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp7SuffixEeElement>>& GetOp7SuffixEeList();
};

#endif // _ALITTLE_ALittleScriptOp7SuffixElement_H_
