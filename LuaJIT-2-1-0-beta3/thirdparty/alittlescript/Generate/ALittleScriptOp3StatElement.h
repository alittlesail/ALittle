#ifndef _ALITTLE_ALittleScriptOp3StatElement_H_
#define _ALITTLE_ALittleScriptOp3StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp3SuffixElement;
class ALittleScriptOp3SuffixExElement;

class ALittleScriptOp3StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp3StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp3StatElement() { }

private:
    bool m_flag_Op3Suffix = false;
    std::shared_ptr<ALittleScriptOp3SuffixElement> m_cache_Op3Suffix;
public:
    std::shared_ptr<ALittleScriptOp3SuffixElement> GetOp3Suffix();
private:
    bool m_flag_Op3SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp3SuffixExElement>> m_list_Op3SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp3SuffixExElement>>& GetOp3SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp3StatElement_H_
