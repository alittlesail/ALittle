#ifndef _ALITTLE_ALittleScriptTemplateExtendsDecElement_H_
#define _ALITTLE_ALittleScriptTemplateExtendsDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeElement;
class ALittleScriptTemplateExtendsClassDecElement;
class ALittleScriptTemplateExtendsStructDecElement;
class ALittleScriptStringElement;

class ALittleScriptTemplateExtendsDecElement : public ABnfNodeElement
{
public:
    ALittleScriptTemplateExtendsDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptTemplateExtendsDecElement() { }

private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType();
private:
    bool m_flag_TemplateExtendsClassDec = false;
    std::shared_ptr<ALittleScriptTemplateExtendsClassDecElement> m_cache_TemplateExtendsClassDec;
public:
    std::shared_ptr<ALittleScriptTemplateExtendsClassDecElement> GetTemplateExtendsClassDec();
private:
    bool m_flag_TemplateExtendsStructDec = false;
    std::shared_ptr<ALittleScriptTemplateExtendsStructDecElement> m_cache_TemplateExtendsStructDec;
public:
    std::shared_ptr<ALittleScriptTemplateExtendsStructDecElement> GetTemplateExtendsStructDec();
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptTemplateExtendsDecElement_H_
