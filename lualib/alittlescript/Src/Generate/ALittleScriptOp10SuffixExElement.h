#ifndef _ALITTLE_ALittleScriptOp10SuffixExElement_H_
#define _ALITTLE_ALittleScriptOp10SuffixExElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp10SuffixElement;
class ALittleScriptOp11SuffixElement;
class ALittleScriptOp12SuffixElement;

class ALittleScriptOp10SuffixExElement : public ABnfNodeElement
{
public:
    ALittleScriptOp10SuffixExElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp10SuffixExElement() { }

private:
    bool m_flag_Op10Suffix = false;
    std::shared_ptr<ALittleScriptOp10SuffixElement> m_cache_Op10Suffix;
public:
    std::shared_ptr<ALittleScriptOp10SuffixElement> GetOp10Suffix();
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

#endif // _ALITTLE_ALittleScriptOp10SuffixExElement_H_
