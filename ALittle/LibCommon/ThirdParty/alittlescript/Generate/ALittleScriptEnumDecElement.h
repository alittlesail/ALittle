#ifndef _ALITTLE_ALittleScriptEnumDecElement_H_
#define _ALITTLE_ALittleScriptEnumDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptEnumNameDecElement;
class ALittleScriptEnumBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptEnumDecElement : public ABnfNodeElement
{
public:
    ALittleScriptEnumDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptEnumDecElement() { }

private:
    bool m_flag_EnumNameDec = false;
    std::shared_ptr<ALittleScriptEnumNameDecElement> m_cache_EnumNameDec;
public:
    std::shared_ptr<ALittleScriptEnumNameDecElement> GetEnumNameDec();
private:
    bool m_flag_EnumBodyDec = false;
    std::shared_ptr<ALittleScriptEnumBodyDecElement> m_cache_EnumBodyDec;
public:
    std::shared_ptr<ALittleScriptEnumBodyDecElement> GetEnumBodyDec();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptEnumDecElement_H_
