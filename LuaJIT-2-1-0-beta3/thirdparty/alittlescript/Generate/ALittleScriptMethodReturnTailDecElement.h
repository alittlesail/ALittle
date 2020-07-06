#ifndef _ALITTLE_ALittleScriptMethodReturnTailDecElement_H_
#define _ALITTLE_ALittleScriptMethodReturnTailDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptStringElement;

class ALittleScriptMethodReturnTailDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodReturnTailDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodReturnTailDecElement() { }

private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptMethodReturnTailDecElement_H_
