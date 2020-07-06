#ifndef _ALITTLE_ALittleScriptGlobalMethodDecElement_H_
#define _ALITTLE_ALittleScriptGlobalMethodDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptTemplateDecElement;
class ALittleScriptMethodNameDecElement;
class ALittleScriptMethodParamDecElement;
class ALittleScriptMethodReturnDecElement;
class ALittleScriptMethodBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptGlobalMethodDecElement : public ABnfNodeElement
{
public:
    ALittleScriptGlobalMethodDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGlobalMethodDecElement() { }

private:
    bool m_flag_TemplateDec = false;
    std::shared_ptr<ALittleScriptTemplateDecElement> m_cache_TemplateDec;
public:
    std::shared_ptr<ALittleScriptTemplateDecElement> GetTemplateDec();
private:
    bool m_flag_MethodNameDec = false;
    std::shared_ptr<ALittleScriptMethodNameDecElement> m_cache_MethodNameDec;
public:
    std::shared_ptr<ALittleScriptMethodNameDecElement> GetMethodNameDec();
private:
    bool m_flag_MethodParamDec = false;
    std::shared_ptr<ALittleScriptMethodParamDecElement> m_cache_MethodParamDec;
public:
    std::shared_ptr<ALittleScriptMethodParamDecElement> GetMethodParamDec();
private:
    bool m_flag_MethodReturnDec = false;
    std::shared_ptr<ALittleScriptMethodReturnDecElement> m_cache_MethodReturnDec;
public:
    std::shared_ptr<ALittleScriptMethodReturnDecElement> GetMethodReturnDec();
private:
    bool m_flag_MethodBodyDec = false;
    std::shared_ptr<ALittleScriptMethodBodyDecElement> m_cache_MethodBodyDec;
public:
    std::shared_ptr<ALittleScriptMethodBodyDecElement> GetMethodBodyDec();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptGlobalMethodDecElement_H_
