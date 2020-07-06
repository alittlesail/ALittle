#ifndef _ALITTLE_ALittleScriptOp2ValueElement_H_
#define _ALITTLE_ALittleScriptOp2ValueElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp2Element;
class ALittleScriptValueFactorStatElement;

class ALittleScriptOp2ValueElement : public ABnfNodeElement
{
public:
    ALittleScriptOp2ValueElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp2ValueElement() { }

private:
    bool m_flag_Op2 = false;
    std::shared_ptr<ALittleScriptOp2Element> m_cache_Op2;
public:
    std::shared_ptr<ALittleScriptOp2Element> GetOp2();
private:
    bool m_flag_ValueFactorStat = false;
    std::shared_ptr<ALittleScriptValueFactorStatElement> m_cache_ValueFactorStat;
public:
    std::shared_ptr<ALittleScriptValueFactorStatElement> GetValueFactorStat();
};

#endif // _ALITTLE_ALittleScriptOp2ValueElement_H_
