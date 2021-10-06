#ifndef _ALITTLE_ALittleScriptOpNewStatElement_H_
#define _ALITTLE_ALittleScriptOpNewStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptCustomTypeElement;
class ALittleScriptGenericTypeElement;
class ALittleScriptValueStatElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptOpNewStatElement : public ABnfNodeElement
{
public:
    ALittleScriptOpNewStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOpNewStatElement() { }

private:
    bool m_flag_CustomType = false;
    std::shared_ptr<ALittleScriptCustomTypeElement> m_cache_CustomType;
public:
    std::shared_ptr<ALittleScriptCustomTypeElement> GetCustomType();
private:
    bool m_flag_GenericType = false;
    std::shared_ptr<ALittleScriptGenericTypeElement> m_cache_GenericType;
public:
    std::shared_ptr<ALittleScriptGenericTypeElement> GetGenericType();
private:
    bool m_flag_ValueStat = false;
    std::vector<std::shared_ptr<ALittleScriptValueStatElement>> m_list_ValueStat;
public:
    const std::vector<std::shared_ptr<ALittleScriptValueStatElement>>& GetValueStatList();
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

#endif // _ALITTLE_ALittleScriptOpNewStatElement_H_
