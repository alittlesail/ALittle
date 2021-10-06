#ifndef _ALITTLE_ALittleScriptMethodParamOneDecElement_H_
#define _ALITTLE_ALittleScriptMethodParamOneDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptMethodParamTailDecElement;
class ALittleScriptModifierElement;
class ALittleScriptAllTypeElement;
class ALittleScriptMethodParamNameDecElement;

class ALittleScriptMethodParamOneDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodParamOneDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodParamOneDecElement() { }

private:
    bool m_flag_MethodParamTailDec = false;
    std::shared_ptr<ALittleScriptMethodParamTailDecElement> m_cache_MethodParamTailDec;
public:
    std::shared_ptr<ALittleScriptMethodParamTailDecElement> GetMethodParamTailDec();
private:
    bool m_flag_Modifier = false;
    std::vector<std::shared_ptr<ALittleScriptModifierElement>> m_list_Modifier;
public:
    const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& GetModifierList();
private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType();
private:
    bool m_flag_MethodParamNameDec = false;
    std::shared_ptr<ALittleScriptMethodParamNameDecElement> m_cache_MethodParamNameDec;
public:
    std::shared_ptr<ALittleScriptMethodParamNameDecElement> GetMethodParamNameDec();
};

#endif // _ALITTLE_ALittleScriptMethodParamOneDecElement_H_
