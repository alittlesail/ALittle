#ifndef _ALITTLE_ALittleScriptValueOpStatElement_H_
#define _ALITTLE_ALittleScriptValueOpStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptValueFactorStatElement;
class ALittleScriptOp5StatElement;
class ALittleScriptOp3StatElement;
class ALittleScriptOp4StatElement;
class ALittleScriptOp6StatElement;
class ALittleScriptOp7StatElement;
class ALittleScriptOp8StatElement;
class ALittleScriptOp9StatElement;
class ALittleScriptOp12StatElement;
class ALittleScriptOp10StatElement;
class ALittleScriptOp11StatElement;

class ALittleScriptValueOpStatElement : public ABnfNodeElement
{
public:
    ALittleScriptValueOpStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptValueOpStatElement() { }

private:
    bool m_flag_ValueFactorStat = false;
    std::shared_ptr<ALittleScriptValueFactorStatElement> m_cache_ValueFactorStat;
public:
    std::shared_ptr<ALittleScriptValueFactorStatElement> GetValueFactorStat();
private:
    bool m_flag_Op5Stat = false;
    std::shared_ptr<ALittleScriptOp5StatElement> m_cache_Op5Stat;
public:
    std::shared_ptr<ALittleScriptOp5StatElement> GetOp5Stat();
private:
    bool m_flag_Op3Stat = false;
    std::shared_ptr<ALittleScriptOp3StatElement> m_cache_Op3Stat;
public:
    std::shared_ptr<ALittleScriptOp3StatElement> GetOp3Stat();
private:
    bool m_flag_Op4Stat = false;
    std::shared_ptr<ALittleScriptOp4StatElement> m_cache_Op4Stat;
public:
    std::shared_ptr<ALittleScriptOp4StatElement> GetOp4Stat();
private:
    bool m_flag_Op6Stat = false;
    std::shared_ptr<ALittleScriptOp6StatElement> m_cache_Op6Stat;
public:
    std::shared_ptr<ALittleScriptOp6StatElement> GetOp6Stat();
private:
    bool m_flag_Op7Stat = false;
    std::shared_ptr<ALittleScriptOp7StatElement> m_cache_Op7Stat;
public:
    std::shared_ptr<ALittleScriptOp7StatElement> GetOp7Stat();
private:
    bool m_flag_Op8Stat = false;
    std::shared_ptr<ALittleScriptOp8StatElement> m_cache_Op8Stat;
public:
    std::shared_ptr<ALittleScriptOp8StatElement> GetOp8Stat();
private:
    bool m_flag_Op9Stat = false;
    std::shared_ptr<ALittleScriptOp9StatElement> m_cache_Op9Stat;
public:
    std::shared_ptr<ALittleScriptOp9StatElement> GetOp9Stat();
private:
    bool m_flag_Op12Stat = false;
    std::shared_ptr<ALittleScriptOp12StatElement> m_cache_Op12Stat;
public:
    std::shared_ptr<ALittleScriptOp12StatElement> GetOp12Stat();
private:
    bool m_flag_Op10Stat = false;
    std::shared_ptr<ALittleScriptOp10StatElement> m_cache_Op10Stat;
public:
    std::shared_ptr<ALittleScriptOp10StatElement> GetOp10Stat();
private:
    bool m_flag_Op11Stat = false;
    std::shared_ptr<ALittleScriptOp11StatElement> m_cache_Op11Stat;
public:
    std::shared_ptr<ALittleScriptOp11StatElement> GetOp11Stat();
};

#endif // _ALITTLE_ALittleScriptValueOpStatElement_H_
