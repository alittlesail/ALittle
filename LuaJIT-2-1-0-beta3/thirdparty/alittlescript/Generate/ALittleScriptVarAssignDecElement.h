#ifndef _ALITTLE_ALittleScriptVarAssignDecElement_H_
#define _ALITTLE_ALittleScriptVarAssignDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptVarAssignNameDecElement;
class ALittleScriptAllTypeElement;
class ALittleScriptStringElement;

class ALittleScriptVarAssignDecElement : public ABnfNodeElement
{
public:
    ALittleScriptVarAssignDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptVarAssignDecElement() { }

private:
    bool m_flag_VarAssignNameDec = false;
    std::shared_ptr<ALittleScriptVarAssignNameDecElement> m_cache_VarAssignNameDec;
public:
    std::shared_ptr<ALittleScriptVarAssignNameDecElement> GetVarAssignNameDec();
private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType();
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptVarAssignDecElement_H_
