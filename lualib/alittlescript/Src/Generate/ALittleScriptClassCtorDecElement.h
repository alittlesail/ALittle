#ifndef _ALITTLE_ALittleScriptClassCtorDecElement_H_
#define _ALITTLE_ALittleScriptClassCtorDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptMethodParamDecElement;
class ALittleScriptMethodBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptClassCtorDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassCtorDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassCtorDecElement() { }

private:
    bool m_flag_MethodParamDec = false;
    std::shared_ptr<ALittleScriptMethodParamDecElement> m_cache_MethodParamDec;
public:
    std::shared_ptr<ALittleScriptMethodParamDecElement> GetMethodParamDec();
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

#endif // _ALITTLE_ALittleScriptClassCtorDecElement_H_
