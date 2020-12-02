#ifndef _ALITTLE_ALittleScriptOp2SuffixExElement_H_
#define _ALITTLE_ALittleScriptOp2SuffixExElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp10SuffixElement;
class ALittleScriptOp3SuffixElement;
class ALittleScriptOp4SuffixElement;
class ALittleScriptOp5SuffixElement;
class ALittleScriptOp6SuffixElement;
class ALittleScriptOp7SuffixElement;
class ALittleScriptOp8SuffixElement;
class ALittleScriptOp12SuffixElement;
class ALittleScriptOp9SuffixElement;
class ALittleScriptOp11SuffixElement;

class ALittleScriptOp2SuffixExElement : public ABnfNodeElement
{
public:
    ALittleScriptOp2SuffixExElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp2SuffixExElement() { }

private:
    bool m_flag_Op10Suffix = false;
    std::shared_ptr<ALittleScriptOp10SuffixElement> m_cache_Op10Suffix;
public:
    std::shared_ptr<ALittleScriptOp10SuffixElement> GetOp10Suffix();
private:
    bool m_flag_Op3Suffix = false;
    std::shared_ptr<ALittleScriptOp3SuffixElement> m_cache_Op3Suffix;
public:
    std::shared_ptr<ALittleScriptOp3SuffixElement> GetOp3Suffix();
private:
    bool m_flag_Op4Suffix = false;
    std::shared_ptr<ALittleScriptOp4SuffixElement> m_cache_Op4Suffix;
public:
    std::shared_ptr<ALittleScriptOp4SuffixElement> GetOp4Suffix();
private:
    bool m_flag_Op5Suffix = false;
    std::shared_ptr<ALittleScriptOp5SuffixElement> m_cache_Op5Suffix;
public:
    std::shared_ptr<ALittleScriptOp5SuffixElement> GetOp5Suffix();
private:
    bool m_flag_Op6Suffix = false;
    std::shared_ptr<ALittleScriptOp6SuffixElement> m_cache_Op6Suffix;
public:
    std::shared_ptr<ALittleScriptOp6SuffixElement> GetOp6Suffix();
private:
    bool m_flag_Op7Suffix = false;
    std::shared_ptr<ALittleScriptOp7SuffixElement> m_cache_Op7Suffix;
public:
    std::shared_ptr<ALittleScriptOp7SuffixElement> GetOp7Suffix();
private:
    bool m_flag_Op8Suffix = false;
    std::shared_ptr<ALittleScriptOp8SuffixElement> m_cache_Op8Suffix;
public:
    std::shared_ptr<ALittleScriptOp8SuffixElement> GetOp8Suffix();
private:
    bool m_flag_Op12Suffix = false;
    std::shared_ptr<ALittleScriptOp12SuffixElement> m_cache_Op12Suffix;
public:
    std::shared_ptr<ALittleScriptOp12SuffixElement> GetOp12Suffix();
private:
    bool m_flag_Op9Suffix = false;
    std::shared_ptr<ALittleScriptOp9SuffixElement> m_cache_Op9Suffix;
public:
    std::shared_ptr<ALittleScriptOp9SuffixElement> GetOp9Suffix();
private:
    bool m_flag_Op11Suffix = false;
    std::shared_ptr<ALittleScriptOp11SuffixElement> m_cache_Op11Suffix;
public:
    std::shared_ptr<ALittleScriptOp11SuffixElement> GetOp11Suffix();
};

#endif // _ALITTLE_ALittleScriptOp2SuffixExElement_H_
