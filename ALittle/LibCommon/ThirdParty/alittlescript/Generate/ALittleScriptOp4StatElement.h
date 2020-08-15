#ifndef _ALITTLE_ALittleScriptOp4StatElement_H_
#define _ALITTLE_ALittleScriptOp4StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp4SuffixElement;
class ALittleScriptOp4SuffixExElement;

class ALittleScriptOp4StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp4StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp4StatElement() { }

private:
    bool m_flag_Op4Suffix = false;
    std::shared_ptr<ALittleScriptOp4SuffixElement> m_cache_Op4Suffix;
public:
    std::shared_ptr<ALittleScriptOp4SuffixElement> GetOp4Suffix();
private:
    bool m_flag_Op4SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp4SuffixExElement>> m_list_Op4SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp4SuffixExElement>>& GetOp4SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp4StatElement_H_
