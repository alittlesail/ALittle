#ifndef _ALITTLE_ALittleScriptOp9StatElement_H_
#define _ALITTLE_ALittleScriptOp9StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp9SuffixElement;
class ALittleScriptOp9SuffixExElement;

class ALittleScriptOp9StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp9StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp9StatElement() { }

private:
    bool m_flag_Op9Suffix = false;
    std::shared_ptr<ALittleScriptOp9SuffixElement> m_cache_Op9Suffix;
public:
    std::shared_ptr<ALittleScriptOp9SuffixElement> GetOp9Suffix();
private:
    bool m_flag_Op9SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp9SuffixExElement>> m_list_Op9SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp9SuffixExElement>>& GetOp9SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp9StatElement_H_
