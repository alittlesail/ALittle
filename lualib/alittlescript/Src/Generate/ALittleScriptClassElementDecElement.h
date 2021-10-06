#ifndef _ALITTLE_ALittleScriptClassElementDecElement_H_
#define _ALITTLE_ALittleScriptClassElementDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptModifierElement;
class ALittleScriptClassSetterDecElement;
class ALittleScriptClassCtorDecElement;
class ALittleScriptClassStaticDecElement;
class ALittleScriptClassGetterDecElement;
class ALittleScriptClassVarDecElement;
class ALittleScriptClassMethodDecElement;

class ALittleScriptClassElementDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassElementDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassElementDecElement() { }

private:
    bool m_flag_Modifier = false;
    std::vector<std::shared_ptr<ALittleScriptModifierElement>> m_list_Modifier;
public:
    const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& GetModifierList();
private:
    bool m_flag_ClassSetterDec = false;
    std::shared_ptr<ALittleScriptClassSetterDecElement> m_cache_ClassSetterDec;
public:
    std::shared_ptr<ALittleScriptClassSetterDecElement> GetClassSetterDec();
private:
    bool m_flag_ClassCtorDec = false;
    std::shared_ptr<ALittleScriptClassCtorDecElement> m_cache_ClassCtorDec;
public:
    std::shared_ptr<ALittleScriptClassCtorDecElement> GetClassCtorDec();
private:
    bool m_flag_ClassStaticDec = false;
    std::shared_ptr<ALittleScriptClassStaticDecElement> m_cache_ClassStaticDec;
public:
    std::shared_ptr<ALittleScriptClassStaticDecElement> GetClassStaticDec();
private:
    bool m_flag_ClassGetterDec = false;
    std::shared_ptr<ALittleScriptClassGetterDecElement> m_cache_ClassGetterDec;
public:
    std::shared_ptr<ALittleScriptClassGetterDecElement> GetClassGetterDec();
private:
    bool m_flag_ClassVarDec = false;
    std::shared_ptr<ALittleScriptClassVarDecElement> m_cache_ClassVarDec;
public:
    std::shared_ptr<ALittleScriptClassVarDecElement> GetClassVarDec();
private:
    bool m_flag_ClassMethodDec = false;
    std::shared_ptr<ALittleScriptClassMethodDecElement> m_cache_ClassMethodDec;
public:
    std::shared_ptr<ALittleScriptClassMethodDecElement> GetClassMethodDec();
};

#endif // _ALITTLE_ALittleScriptClassElementDecElement_H_
