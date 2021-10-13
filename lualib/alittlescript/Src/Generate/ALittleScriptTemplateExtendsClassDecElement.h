#ifndef _ALITTLE_ALittleScriptTemplateExtendsClassDecElement_H_
#define _ALITTLE_ALittleScriptTemplateExtendsClassDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptKeyElement;

class ALittleScriptTemplateExtendsClassDecElement : public ABnfNodeElement
{
public:
    ALittleScriptTemplateExtendsClassDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptTemplateExtendsClassDecElement() { }

private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptTemplateExtendsClassDecElement_H_
