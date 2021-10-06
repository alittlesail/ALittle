#ifndef _ALITTLE_ALittleScriptOp12SuffixExElement_H_
#define _ALITTLE_ALittleScriptOp12SuffixExElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp12SuffixElement;

class ALittleScriptOp12SuffixExElement : public ABnfNodeElement
{
public:
    ALittleScriptOp12SuffixExElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp12SuffixExElement() { }

private:
    bool m_flag_Op12Suffix = false;
    std::shared_ptr<ALittleScriptOp12SuffixElement> m_cache_Op12Suffix;
public:
    std::shared_ptr<ALittleScriptOp12SuffixElement> GetOp12Suffix();
};

#endif // _ALITTLE_ALittleScriptOp12SuffixExElement_H_
