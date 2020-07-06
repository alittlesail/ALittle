#ifndef _ALITTLE_ALittleScriptClassVarDecElement_H_
#define _ALITTLE_ALittleScriptClassVarDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeElement;
class ALittleScriptClassVarNameDecElement;
class ALittleScriptClassVarValueDecElement;
class ALittleScriptStringElement;

class ALittleScriptClassVarDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassVarDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassVarDecElement() { }

private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType();
private:
    bool m_flag_ClassVarNameDec = false;
    std::shared_ptr<ALittleScriptClassVarNameDecElement> m_cache_ClassVarNameDec;
public:
    std::shared_ptr<ALittleScriptClassVarNameDecElement> GetClassVarNameDec();
private:
    bool m_flag_ClassVarValueDec = false;
    std::shared_ptr<ALittleScriptClassVarValueDecElement> m_cache_ClassVarValueDec;
public:
    std::shared_ptr<ALittleScriptClassVarValueDecElement> GetClassVarValueDec();
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptClassVarDecElement_H_
