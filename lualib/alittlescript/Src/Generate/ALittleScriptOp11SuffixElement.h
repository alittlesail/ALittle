#ifndef _ALITTLE_ALittleScriptOp11SuffixElement_H_
#define _ALITTLE_ALittleScriptOp11SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp11Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp11SuffixEeElement;

class ALittleScriptOp11SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp11SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp11SuffixElement() { }

private:
    bool m_flag_Op11 = false;
    std::shared_ptr<ALittleScriptOp11Element> m_cache_Op11;
public:
    std::shared_ptr<ALittleScriptOp11Element> GetOp11();
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
    bool m_flag_Op11SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp11SuffixEeElement>> m_list_Op11SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp11SuffixEeElement>>& GetOp11SuffixEeList();
};

#endif // _ALITTLE_ALittleScriptOp11SuffixElement_H_
