#ifndef _ALITTLE_ALittleScriptOp10SuffixElement_H_
#define _ALITTLE_ALittleScriptOp10SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp10Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp10SuffixEeElement;

class ALittleScriptOp10SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp10SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp10SuffixElement() { }

private:
    bool m_flag_Op10 = false;
    std::shared_ptr<ALittleScriptOp10Element> m_cache_Op10;
public:
    std::shared_ptr<ALittleScriptOp10Element> GetOp10();
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
    bool m_flag_Op10SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp10SuffixEeElement>> m_list_Op10SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp10SuffixEeElement>>& GetOp10SuffixEeList();
};

#endif // _ALITTLE_ALittleScriptOp10SuffixElement_H_
