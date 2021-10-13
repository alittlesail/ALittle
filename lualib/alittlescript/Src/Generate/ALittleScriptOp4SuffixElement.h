#ifndef _ALITTLE_ALittleScriptOp4SuffixElement_H_
#define _ALITTLE_ALittleScriptOp4SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp4Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp4SuffixEeElement;

class ALittleScriptOp4SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp4SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp4SuffixElement() { }

private:
    bool m_flag_Op4 = false;
    std::shared_ptr<ALittleScriptOp4Element> m_cache_Op4;
public:
    std::shared_ptr<ALittleScriptOp4Element> GetOp4();
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
    bool m_flag_Op4SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp4SuffixEeElement>> m_list_Op4SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp4SuffixEeElement>>& GetOp4SuffixEeList();
};

#endif // _ALITTLE_ALittleScriptOp4SuffixElement_H_
