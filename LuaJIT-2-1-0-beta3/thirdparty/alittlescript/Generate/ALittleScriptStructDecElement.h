#ifndef _ALITTLE_ALittleScriptStructDecElement_H_
#define _ALITTLE_ALittleScriptStructDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptStructNameDecElement;
class ALittleScriptStructExtendsDecElement;
class ALittleScriptStructBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptStructDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructDecElement() { }

private:
    bool m_flag_StructNameDec = false;
    std::shared_ptr<ALittleScriptStructNameDecElement> m_cache_StructNameDec;
public:
    std::shared_ptr<ALittleScriptStructNameDecElement> GetStructNameDec();
private:
    bool m_flag_StructExtendsDec = false;
    std::shared_ptr<ALittleScriptStructExtendsDecElement> m_cache_StructExtendsDec;
public:
    std::shared_ptr<ALittleScriptStructExtendsDecElement> GetStructExtendsDec();
private:
    bool m_flag_StructBodyDec = false;
    std::shared_ptr<ALittleScriptStructBodyDecElement> m_cache_StructBodyDec;
public:
    std::shared_ptr<ALittleScriptStructBodyDecElement> GetStructBodyDec();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptStructDecElement_H_
