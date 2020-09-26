#ifndef _ALITTLE_ALittleScriptNamespaceElementDecElement_H_
#define _ALITTLE_ALittleScriptNamespaceElementDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptModifierElement;
class ALittleScriptEnumDecElement;
class ALittleScriptStructDecElement;
class ALittleScriptOpAssignExprElement;
class ALittleScriptGlobalMethodDecElement;
class ALittleScriptClassDecElement;
class ALittleScriptUsingDecElement;
class ALittleScriptInstanceDecElement;

class ALittleScriptNamespaceElementDecElement : public ABnfNodeElement
{
public:
    ALittleScriptNamespaceElementDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptNamespaceElementDecElement() { }

private:
    bool m_flag_Modifier = false;
    std::vector<std::shared_ptr<ALittleScriptModifierElement>> m_list_Modifier;
public:
    const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& GetModifierList();
private:
    bool m_flag_EnumDec = false;
    std::shared_ptr<ALittleScriptEnumDecElement> m_cache_EnumDec;
public:
    std::shared_ptr<ALittleScriptEnumDecElement> GetEnumDec();
private:
    bool m_flag_StructDec = false;
    std::shared_ptr<ALittleScriptStructDecElement> m_cache_StructDec;
public:
    std::shared_ptr<ALittleScriptStructDecElement> GetStructDec();
private:
    bool m_flag_OpAssignExpr = false;
    std::shared_ptr<ALittleScriptOpAssignExprElement> m_cache_OpAssignExpr;
public:
    std::shared_ptr<ALittleScriptOpAssignExprElement> GetOpAssignExpr();
private:
    bool m_flag_GlobalMethodDec = false;
    std::shared_ptr<ALittleScriptGlobalMethodDecElement> m_cache_GlobalMethodDec;
public:
    std::shared_ptr<ALittleScriptGlobalMethodDecElement> GetGlobalMethodDec();
private:
    bool m_flag_ClassDec = false;
    std::shared_ptr<ALittleScriptClassDecElement> m_cache_ClassDec;
public:
    std::shared_ptr<ALittleScriptClassDecElement> GetClassDec();
private:
    bool m_flag_UsingDec = false;
    std::shared_ptr<ALittleScriptUsingDecElement> m_cache_UsingDec;
public:
    std::shared_ptr<ALittleScriptUsingDecElement> GetUsingDec();
private:
    bool m_flag_InstanceDec = false;
    std::shared_ptr<ALittleScriptInstanceDecElement> m_cache_InstanceDec;
public:
    std::shared_ptr<ALittleScriptInstanceDecElement> GetInstanceDec();
};

#endif // _ALITTLE_ALittleScriptNamespaceElementDecElement_H_
