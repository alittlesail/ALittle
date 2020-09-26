#ifndef _ALITTLE_ALittleScriptOp4SuffixEeElement_H_
#define _ALITTLE_ALittleScriptOp4SuffixEeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp3SuffixElement;

class ALittleScriptOp4SuffixEeElement : public ABnfNodeElement
{
public:
    ALittleScriptOp4SuffixEeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp4SuffixEeElement() { }

private:
    bool m_flag_Op3Suffix = false;
    std::shared_ptr<ALittleScriptOp3SuffixElement> m_cache_Op3Suffix;
public:
    std::shared_ptr<ALittleScriptOp3SuffixElement> GetOp3Suffix();
};

#endif // _ALITTLE_ALittleScriptOp4SuffixEeElement_H_
