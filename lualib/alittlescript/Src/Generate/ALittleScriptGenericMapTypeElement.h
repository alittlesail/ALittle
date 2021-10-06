#ifndef _ALITTLE_ALittleScriptGenericMapTypeElement_H_
#define _ALITTLE_ALittleScriptGenericMapTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptGenericMapTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericMapTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericMapTypeElement() { }

private:
    bool m_flag_AllType = false;
    std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> m_list_AllType;
public:
    const std::vector<std::shared_ptr<ALittleScriptAllTypeElement>>& GetAllTypeList();
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

#endif // _ALITTLE_ALittleScriptGenericMapTypeElement_H_
