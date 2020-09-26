#ifndef _ALITTLE_ALittleScriptOp1ExprElement_H_
#define _ALITTLE_ALittleScriptOp1ExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp1Element;
class ALittleScriptValueStatElement;
class ALittleScriptStringElement;

class ALittleScriptOp1ExprElement : public ABnfNodeElement
{
public:
    ALittleScriptOp1ExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp1ExprElement() { }

private:
    bool m_flag_Op1 = false;
    std::shared_ptr<ALittleScriptOp1Element> m_cache_Op1;
public:
    std::shared_ptr<ALittleScriptOp1Element> GetOp1();
private:
    bool m_flag_ValueStat = false;
    std::shared_ptr<ALittleScriptValueStatElement> m_cache_ValueStat;
public:
    std::shared_ptr<ALittleScriptValueStatElement> GetValueStat();
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptOp1ExprElement_H_
