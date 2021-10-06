#ifndef _ALITTLE_ALittleScriptOp7StatElement_H_
#define _ALITTLE_ALittleScriptOp7StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp7SuffixElement;
class ALittleScriptOp7SuffixExElement;

class ALittleScriptOp7StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp7StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp7StatElement() { }

private:
    bool m_flag_Op7Suffix = false;
    std::shared_ptr<ALittleScriptOp7SuffixElement> m_cache_Op7Suffix;
public:
    std::shared_ptr<ALittleScriptOp7SuffixElement> GetOp7Suffix();
private:
    bool m_flag_Op7SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp7SuffixExElement>> m_list_Op7SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp7SuffixExElement>>& GetOp7SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp7StatElement_H_
