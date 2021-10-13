#ifndef _ALITTLE_ALittleScriptUsingDecElement_H_
#define _ALITTLE_ALittleScriptUsingDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptUsingNameDecElement;
class ALittleScriptAllTypeElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptUsingDecElement : public ABnfNodeElement
{
public:
    ALittleScriptUsingDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptUsingDecElement() { }

private:
    bool m_flag_UsingNameDec = false;
    std::shared_ptr<ALittleScriptUsingNameDecElement> m_cache_UsingNameDec;
public:
    std::shared_ptr<ALittleScriptUsingNameDecElement> GetUsingNameDec();
private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptUsingDecElement_H_
