#ifndef _ALITTLE_ALittleScriptClassExtendsDecElement_H_
#define _ALITTLE_ALittleScriptClassExtendsDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptNamespaceNameDecElement;
class ALittleScriptClassNameDecElement;
class ALittleScriptStringElement;

class ALittleScriptClassExtendsDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassExtendsDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassExtendsDecElement() { }

private:
    bool m_flag_NamespaceNameDec = false;
    std::shared_ptr<ALittleScriptNamespaceNameDecElement> m_cache_NamespaceNameDec;
public:
    std::shared_ptr<ALittleScriptNamespaceNameDecElement> GetNamespaceNameDec();
private:
    bool m_flag_ClassNameDec = false;
    std::shared_ptr<ALittleScriptClassNameDecElement> m_cache_ClassNameDec;
public:
    std::shared_ptr<ALittleScriptClassNameDecElement> GetClassNameDec();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptClassExtendsDecElement_H_
