#ifndef _ALITTLE_ALittleScriptReflectValueElement_H_
#define _ALITTLE_ALittleScriptReflectValueElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptReflectCustomTypeElement;
class ALittleScriptReflectValueStatElement;
class ALittleScriptKeyElement;

class ALittleScriptReflectValueElement : public ABnfNodeElement
{
public:
    ALittleScriptReflectValueElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptReflectValueElement() { }

private:
    bool m_flag_ReflectCustomType = false;
    std::shared_ptr<ALittleScriptReflectCustomTypeElement> m_cache_ReflectCustomType;
public:
    std::shared_ptr<ALittleScriptReflectCustomTypeElement> GetReflectCustomType();
private:
    bool m_flag_ReflectValueStat = false;
    std::shared_ptr<ALittleScriptReflectValueStatElement> m_cache_ReflectValueStat;
public:
    std::shared_ptr<ALittleScriptReflectValueStatElement> GetReflectValueStat();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptReflectValueElement_H_
