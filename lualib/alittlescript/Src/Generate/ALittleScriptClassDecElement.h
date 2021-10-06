#ifndef _ALITTLE_ALittleScriptClassDecElement_H_
#define _ALITTLE_ALittleScriptClassDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptClassExtendsDecElement;
class ALittleScriptClassNameDecElement;
class ALittleScriptTemplateDecElement;
class ALittleScriptClassBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptClassDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassDecElement() { }

private:
    bool m_flag_ClassExtendsDec = false;
    std::shared_ptr<ALittleScriptClassExtendsDecElement> m_cache_ClassExtendsDec;
public:
    std::shared_ptr<ALittleScriptClassExtendsDecElement> GetClassExtendsDec();
private:
    bool m_flag_ClassNameDec = false;
    std::shared_ptr<ALittleScriptClassNameDecElement> m_cache_ClassNameDec;
public:
    std::shared_ptr<ALittleScriptClassNameDecElement> GetClassNameDec();
private:
    bool m_flag_TemplateDec = false;
    std::shared_ptr<ALittleScriptTemplateDecElement> m_cache_TemplateDec;
public:
    std::shared_ptr<ALittleScriptTemplateDecElement> GetTemplateDec();
private:
    bool m_flag_ClassBodyDec = false;
    std::shared_ptr<ALittleScriptClassBodyDecElement> m_cache_ClassBodyDec;
public:
    std::shared_ptr<ALittleScriptClassBodyDecElement> GetClassBodyDec();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptClassDecElement_H_
