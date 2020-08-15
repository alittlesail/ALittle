#ifndef _ALITTLE_ALittleScriptValueStatElement_H_
#define _ALITTLE_ALittleScriptValueStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOpNewListStatElement;
class ALittleScriptOpNewStatElement;
class ALittleScriptBindStatElement;
class ALittleScriptTcallStatElement;
class ALittleScriptOp2StatElement;
class ALittleScriptValueOpStatElement;

class ALittleScriptValueStatElement : public ABnfNodeElement
{
public:
    ALittleScriptValueStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptValueStatElement() { }

private:
    bool m_flag_OpNewListStat = false;
    std::shared_ptr<ALittleScriptOpNewListStatElement> m_cache_OpNewListStat;
public:
    std::shared_ptr<ALittleScriptOpNewListStatElement> GetOpNewListStat();
private:
    bool m_flag_OpNewStat = false;
    std::shared_ptr<ALittleScriptOpNewStatElement> m_cache_OpNewStat;
public:
    std::shared_ptr<ALittleScriptOpNewStatElement> GetOpNewStat();
private:
    bool m_flag_BindStat = false;
    std::shared_ptr<ALittleScriptBindStatElement> m_cache_BindStat;
public:
    std::shared_ptr<ALittleScriptBindStatElement> GetBindStat();
private:
    bool m_flag_TcallStat = false;
    std::shared_ptr<ALittleScriptTcallStatElement> m_cache_TcallStat;
public:
    std::shared_ptr<ALittleScriptTcallStatElement> GetTcallStat();
private:
    bool m_flag_Op2Stat = false;
    std::shared_ptr<ALittleScriptOp2StatElement> m_cache_Op2Stat;
public:
    std::shared_ptr<ALittleScriptOp2StatElement> GetOp2Stat();
private:
    bool m_flag_ValueOpStat = false;
    std::shared_ptr<ALittleScriptValueOpStatElement> m_cache_ValueOpStat;
public:
    std::shared_ptr<ALittleScriptValueOpStatElement> GetValueOpStat();
};

#endif // _ALITTLE_ALittleScriptValueStatElement_H_
