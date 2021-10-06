#ifndef _ALITTLE_ALittleScriptClassSetterDecElement_H_
#define _ALITTLE_ALittleScriptClassSetterDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptMethodNameDecElement;
class ALittleScriptMethodSetterParamDecElement;
class ALittleScriptMethodBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptClassSetterDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassSetterDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassSetterDecElement() { }

private:
    bool m_flag_MethodNameDec = false;
    std::shared_ptr<ALittleScriptMethodNameDecElement> m_cache_MethodNameDec;
public:
    std::shared_ptr<ALittleScriptMethodNameDecElement> GetMethodNameDec();
private:
    bool m_flag_MethodSetterParamDec = false;
    std::shared_ptr<ALittleScriptMethodSetterParamDecElement> m_cache_MethodSetterParamDec;
public:
    std::shared_ptr<ALittleScriptMethodSetterParamDecElement> GetMethodSetterParamDec();
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

#endif // _ALITTLE_ALittleScriptClassSetterDecElement_H_
