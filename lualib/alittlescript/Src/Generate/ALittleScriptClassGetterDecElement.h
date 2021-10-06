#ifndef _ALITTLE_ALittleScriptClassGetterDecElement_H_
#define _ALITTLE_ALittleScriptClassGetterDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptMethodNameDecElement;
class ALittleScriptMethodGetterParamDecElement;
class ALittleScriptAllTypeElement;
class ALittleScriptMethodBodyDecElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptClassGetterDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassGetterDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassGetterDecElement() { }

private:
    bool m_flag_MethodNameDec = false;
    std::shared_ptr<ALittleScriptMethodNameDecElement> m_cache_MethodNameDec;
public:
    std::shared_ptr<ALittleScriptMethodNameDecElement> GetMethodNameDec();
private:
    bool m_flag_MethodGetterParamDec = false;
    std::shared_ptr<ALittleScriptMethodGetterParamDecElement> m_cache_MethodGetterParamDec;
public:
    std::shared_ptr<ALittleScriptMethodGetterParamDecElement> GetMethodGetterParamDec();
private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType();
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
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptClassGetterDecElement_H_
