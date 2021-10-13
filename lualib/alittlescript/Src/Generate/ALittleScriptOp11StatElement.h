#ifndef _ALITTLE_ALittleScriptOp11StatElement_H_
#define _ALITTLE_ALittleScriptOp11StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptOp11SuffixElement;
class ALittleScriptOp11SuffixExElement;

class ALittleScriptOp11StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp11StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp11StatElement() { }

private:
    bool m_flag_Op11Suffix = false;
    std::shared_ptr<ALittleScriptOp11SuffixElement> m_cache_Op11Suffix;
public:
    std::shared_ptr<ALittleScriptOp11SuffixElement> GetOp11Suffix();
private:
    bool m_flag_Op11SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp11SuffixExElement>> m_list_Op11SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp11SuffixExElement>>& GetOp11SuffixExList();
};

#endif // _ALITTLE_ALittleScriptOp11StatElement_H_
