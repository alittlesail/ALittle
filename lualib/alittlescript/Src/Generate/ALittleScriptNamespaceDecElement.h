#ifndef _ALITTLE_ALittleScriptNamespaceDecElement_H_
#define _ALITTLE_ALittleScriptNamespaceDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptModifierElement;
class ALittleScriptNamespaceElementDecElement;
class ALittleScriptNamespaceNameDecElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptNamespaceDecElement : public ABnfNodeElement
{
public:
    ALittleScriptNamespaceDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptNamespaceDecElement() { }

private:
    bool m_flag_Modifier = false;
    std::vector<std::shared_ptr<ALittleScriptModifierElement>> m_list_Modifier;
public:
    const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& GetModifierList();
private:
    bool m_flag_NamespaceElementDec = false;
    std::vector<std::shared_ptr<ALittleScriptNamespaceElementDecElement>> m_list_NamespaceElementDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptNamespaceElementDecElement>>& GetNamespaceElementDecList();
private:
    bool m_flag_NamespaceNameDec = false;
    std::shared_ptr<ALittleScriptNamespaceNameDecElement> m_cache_NamespaceNameDec;
public:
    std::shared_ptr<ALittleScriptNamespaceNameDecElement> GetNamespaceNameDec();
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

#endif // _ALITTLE_ALittleScriptNamespaceDecElement_H_
