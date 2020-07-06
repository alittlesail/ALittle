#ifndef _ALITTLE_ALittleScriptValueFactorStatElement_H_
#define _ALITTLE_ALittleScriptValueFactorStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptWrapValueStatElement;
class ALittleScriptMethodParamTailDecElement;
class ALittleScriptConstValueElement;
class ALittleScriptReflectValueElement;
class ALittleScriptPathsValueElement;
class ALittleScriptPropertyValueElement;
class ALittleScriptCoroutineStatElement;

class ALittleScriptValueFactorStatElement : public ABnfNodeElement
{
public:
    ALittleScriptValueFactorStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptValueFactorStatElement() { }

private:
    bool m_flag_WrapValueStat = false;
    std::shared_ptr<ALittleScriptWrapValueStatElement> m_cache_WrapValueStat;
public:
    std::shared_ptr<ALittleScriptWrapValueStatElement> GetWrapValueStat();
private:
    bool m_flag_MethodParamTailDec = false;
    std::shared_ptr<ALittleScriptMethodParamTailDecElement> m_cache_MethodParamTailDec;
public:
    std::shared_ptr<ALittleScriptMethodParamTailDecElement> GetMethodParamTailDec();
private:
    bool m_flag_ConstValue = false;
    std::shared_ptr<ALittleScriptConstValueElement> m_cache_ConstValue;
public:
    std::shared_ptr<ALittleScriptConstValueElement> GetConstValue();
private:
    bool m_flag_ReflectValue = false;
    std::shared_ptr<ALittleScriptReflectValueElement> m_cache_ReflectValue;
public:
    std::shared_ptr<ALittleScriptReflectValueElement> GetReflectValue();
private:
    bool m_flag_PathsValue = false;
    std::shared_ptr<ALittleScriptPathsValueElement> m_cache_PathsValue;
public:
    std::shared_ptr<ALittleScriptPathsValueElement> GetPathsValue();
private:
    bool m_flag_PropertyValue = false;
    std::shared_ptr<ALittleScriptPropertyValueElement> m_cache_PropertyValue;
public:
    std::shared_ptr<ALittleScriptPropertyValueElement> GetPropertyValue();
private:
    bool m_flag_CoroutineStat = false;
    std::shared_ptr<ALittleScriptCoroutineStatElement> m_cache_CoroutineStat;
public:
    std::shared_ptr<ALittleScriptCoroutineStatElement> GetCoroutineStat();
};

#endif // _ALITTLE_ALittleScriptValueFactorStatElement_H_
