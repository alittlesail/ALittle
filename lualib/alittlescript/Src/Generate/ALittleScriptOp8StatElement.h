#ifndef _ALITTLE_ALittleScriptOp8StatElement_H_
#define _ALITTLE_ALittleScriptOp8StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp8SuffixElement;
class ALittleScriptOp8SuffixExElement;

class ALittleScriptOp8StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp8StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp8StatElement() { }

private:
    bool m_flag_Op8Suffix = false;
    std::shared_ptr<ALittleScriptOp8SuffixElement> m_cache_Op8Suffix;
public:
    std::shared_ptr<ALittleScriptOp8SuffixElement> GetOp8Suffix();
private:
    bool m_flag_Op8SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp8SuffixExElement>> m_list_Op8SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp8SuffixExElement>>& GetOp8SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp8StatElement_H_
