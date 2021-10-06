#ifndef _ALITTLE_ALittleScriptLanguageModifierElement_H_
#define _ALITTLE_ALittleScriptLanguageModifierElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptLanguageBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptLanguageModifierElement : public ABnfNodeElement
{
public:
    ALittleScriptLanguageModifierElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptLanguageModifierElement() { }

private:
    bool m_flag_LanguageBodyDec = false;
    std::shared_ptr<ALittleScriptLanguageBodyDecElement> m_cache_LanguageBodyDec;
public:
    std::shared_ptr<ALittleScriptLanguageBodyDecElement> GetLanguageBodyDec();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptLanguageModifierElement_H_
