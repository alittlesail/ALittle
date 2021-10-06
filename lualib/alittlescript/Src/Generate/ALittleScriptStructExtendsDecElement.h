#ifndef _ALITTLE_ALittleScriptStructExtendsDecElement_H_
#define _ALITTLE_ALittleScriptStructExtendsDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptNamespaceNameDecElement;
class ALittleScriptStructNameDecElement;
class ALittleScriptStringElement;

class ALittleScriptStructExtendsDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructExtendsDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructExtendsDecElement() { }

private:
    bool m_flag_NamespaceNameDec = false;
    std::shared_ptr<ALittleScriptNamespaceNameDecElement> m_cache_NamespaceNameDec;
public:
    std::shared_ptr<ALittleScriptNamespaceNameDecElement> GetNamespaceNameDec();
private:
    bool m_flag_StructNameDec = false;
    std::shared_ptr<ALittleScriptStructNameDecElement> m_cache_StructNameDec;
public:
    std::shared_ptr<ALittleScriptStructNameDecElement> GetStructNameDec();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptStructExtendsDecElement_H_
