#ifndef _ALITTLE_ALittleScriptOp3SuffixElement_H_
#define _ALITTLE_ALittleScriptOp3SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp3Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;

class ALittleScriptOp3SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp3SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp3SuffixElement() { }

private:
    bool m_flag_Op3 = false;
    std::shared_ptr<ALittleScriptOp3Element> m_cache_Op3;
public:
    std::shared_ptr<ALittleScriptOp3Element> GetOp3();
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
};

#endif // _ALITTLE_ALittleScriptOp3SuffixElement_H_
