#ifndef _ALITTLE_ALittleScriptOp11SuffixExElement_H_
#define _ALITTLE_ALittleScriptOp11SuffixExElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp11SuffixElement;
class ALittleScriptOp12SuffixElement;

class ALittleScriptOp11SuffixExElement : public ABnfNodeElement
{
public:
    ALittleScriptOp11SuffixExElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp11SuffixExElement() { }

private:
    bool m_flag_Op11Suffix = false;
    std::shared_ptr<ALittleScriptOp11SuffixElement> m_cache_Op11Suffix;
public:
    std::shared_ptr<ALittleScriptOp11SuffixElement> GetOp11Suffix();
private:
    bool m_flag_Op12Suffix = false;
    std::shared_ptr<ALittleScriptOp12SuffixElement> m_cache_Op12Suffix;
public:
    std::shared_ptr<ALittleScriptOp12SuffixElement> GetOp12Suffix();
};

#endif // _ALITTLE_ALittleScriptOp11SuffixExElement_H_
