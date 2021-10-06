#ifndef _ALITTLE_ALittleScriptOp12StatElement_H_
#define _ALITTLE_ALittleScriptOp12StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp12SuffixElement;
class ALittleScriptOp12SuffixExElement;

class ALittleScriptOp12StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp12StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp12StatElement() { }

private:
    bool m_flag_Op12Suffix = false;
    std::shared_ptr<ALittleScriptOp12SuffixElement> m_cache_Op12Suffix;
public:
    std::shared_ptr<ALittleScriptOp12SuffixElement> GetOp12Suffix();
private:
    bool m_flag_Op12SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp12SuffixExElement>> m_list_Op12SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp12SuffixExElement>>& GetOp12SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp12StatElement_H_
