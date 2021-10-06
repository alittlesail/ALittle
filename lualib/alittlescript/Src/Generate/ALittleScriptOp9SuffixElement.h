#ifndef _ALITTLE_ALittleScriptOp9SuffixElement_H_
#define _ALITTLE_ALittleScriptOp9SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp9Element;
class ALittleScriptOp2ValueElement;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp9SuffixEeElement;

class ALittleScriptOp9SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp9SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp9SuffixElement() { }

private:
    bool m_flag_Op9 = false;
    std::shared_ptr<ALittleScriptOp9Element> m_cache_Op9;
public:
    std::shared_ptr<ALittleScriptOp9Element> GetOp9();
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
    bool m_flag_Op9SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp9SuffixEeElement>> m_list_Op9SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp9SuffixEeElement>>& GetOp9SuffixEeList();
};

#endif // _ALITTLE_ALittleScriptOp9SuffixElement_H_
