#ifndef _ALITTLE_ALittleScriptOp8Element_H_
#define _ALITTLE_ALittleScriptOp8Element_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptStringElement;

class ALittleScriptOp8Element : public ABnfNodeElement
{
public:
    ALittleScriptOp8Element(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp8Element() { }

private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptOp8Element_H_
