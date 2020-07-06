#ifndef _ALITTLE_ALittleScriptTemplateExtendsStructDecElement_H_
#define _ALITTLE_ALittleScriptTemplateExtendsStructDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptKeyElement;

class ALittleScriptTemplateExtendsStructDecElement : public ABnfNodeElement
{
public:
    ALittleScriptTemplateExtendsStructDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptTemplateExtendsStructDecElement() { }

private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptTemplateExtendsStructDecElement_H_
