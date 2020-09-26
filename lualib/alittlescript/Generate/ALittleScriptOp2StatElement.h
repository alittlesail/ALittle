#ifndef _ALITTLE_ALittleScriptOp2StatElement_H_
#define _ALITTLE_ALittleScriptOp2StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp2ValueElement;
class ALittleScriptOp2SuffixExElement;

class ALittleScriptOp2StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp2StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp2StatElement() { }

private:
    bool m_flag_Op2Value = false;
    std::shared_ptr<ALittleScriptOp2ValueElement> m_cache_Op2Value;
public:
    std::shared_ptr<ALittleScriptOp2ValueElement> GetOp2Value();
private:
    bool m_flag_Op2SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp2SuffixExElement>> m_list_Op2SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp2SuffixExElement>>& GetOp2SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp2StatElement_H_
