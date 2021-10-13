#ifndef _ALITTLE_ALittleScriptOp6StatElement_H_
#define _ALITTLE_ALittleScriptOp6StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp6SuffixElement;
class ALittleScriptOp6SuffixExElement;

class ALittleScriptOp6StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp6StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp6StatElement() { }

private:
    bool m_flag_Op6Suffix = false;
    std::shared_ptr<ALittleScriptOp6SuffixElement> m_cache_Op6Suffix;
public:
    std::shared_ptr<ALittleScriptOp6SuffixElement> GetOp6Suffix();
private:
    bool m_flag_Op6SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp6SuffixExElement>> m_list_Op6SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp6SuffixExElement>>& GetOp6SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp6StatElement_H_
