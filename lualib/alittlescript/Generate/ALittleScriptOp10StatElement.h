#ifndef _ALITTLE_ALittleScriptOp10StatElement_H_
#define _ALITTLE_ALittleScriptOp10StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp10SuffixElement;
class ALittleScriptOp10SuffixExElement;

class ALittleScriptOp10StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp10StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp10StatElement() { }

private:
    bool m_flag_Op10Suffix = false;
    std::shared_ptr<ALittleScriptOp10SuffixElement> m_cache_Op10Suffix;
public:
    std::shared_ptr<ALittleScriptOp10SuffixElement> GetOp10Suffix();
private:
    bool m_flag_Op10SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp10SuffixExElement>> m_list_Op10SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp10SuffixExElement>>& GetOp10SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp10StatElement_H_
